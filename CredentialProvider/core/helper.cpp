/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
**
** Copyright	2012 Dominik Pretzsch
**				2017 NetKnights GmbH
**
** Author		Dominik Pretzsch
**				Nils Behlen
**
**    Licensed under the Apache License, Version 2.0 (the "License");
**    you may not use this file except in compliance with the License.
**    You may obtain a copy of the License at
**
**        http://www.apache.org/licenses/LICENSE-2.0
**
**    Unless required by applicable law or agreed to in writing, software
**    distributed under the License is distributed on an "AS IS" BASIS,
**    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**    See the License for the specific language governing permissions and
**    limitations under the License.
**
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "helper.h"
#include "Logger.h"
#include "Configuration.h"

namespace Helper
{
	std::wstring s2ws(const std::string& str)
	{
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.from_bytes(str);
	}

	std::string ws2s(const std::wstring& wstr)
	{
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.to_bytes(wstr);
	}

	PWSTR ws2pwstr(const std::wstring& wstr)
	{
		UNREFERENCED_PARAMETER(wstr);
		//PWSTR ret = new wchar_t[wstr.length + 1];
		//wcscpy_s(ret, (wstr.length+1), wstr.c_str());
		//return ret;
		return nullptr;
	}

	char* s2psz(const std::string& str)
	{
		UNREFERENCED_PARAMETER(str);

		//char* ret = new char[str.length + 1];
		//strcpy_s(ret, (str.length + 1), str.c_str());
		//return ret;
		return nullptr;
	}

	void RedrawGUI()
	{
		DebugPrintLn(__FUNCTION__);

		if (Configuration::Get().provider._pCredentialProviderEvents != NULL)
		{
			Configuration::Get().provider._pCredentialProviderEvents->CredentialsChanged(Configuration::Get().provider._upAdviseContext);
		}
	}

	int GetFirstActiveIPAddress(
		__out_opt char *&ip_addr
	)
	{
		WSAData wsaData;

		if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
			return 1;
		}

		char hostname[80];
		if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) {
			return 2;
		}

		struct hostent *phe = gethostbyname(hostname);

		if (phe == 0) {
			return 3;
		}

		if (phe->h_addr_list[0] != 0)
		{
			struct in_addr addr;
			memcpy(&addr, phe->h_addr_list[0], sizeof(struct in_addr));

			ip_addr = _strdup(inet_ntoa(addr));

			// remove interface identifier from ipv6 addr
			char *ifIdSeparatorPos = strstr(ip_addr, "%");
			if (ifIdSeparatorPos)
			{
				ifIdSeparatorPos[0] = NULL;
			}
		}

		return 0;
	}

	void SeparateUserAndDomainName(
		__in wchar_t *fq_username,
		__out wchar_t *username,
		__in int sizeUsername,
		__out_opt wchar_t *domain,
		__in_opt int sizeDomain
	)
	{
		int pos;
		for (pos = 0; fq_username[pos] != L'\\' && fq_username[pos] != L'@' && fq_username[pos] != NULL; pos++);

		if (fq_username[pos] != NULL)
		{
			if (fq_username[pos] == L'\\')
			{
				int i;
				for (i = 0; i < pos && i < sizeDomain; i++)
					domain[i] = fq_username[i];
				domain[i] = L'\0';

				for (i = 0; fq_username[pos + i + 1] != NULL && i < sizeUsername; i++)
					username[i] = fq_username[pos + i + 1];
				username[i] = L'\0';
			}
			else
			{
				int i;
				for (i = 0; i < pos && i < sizeUsername; i++)
					username[i] = fq_username[i];
				username[i] = L'\0';

				for (i = 0; fq_username[pos + i + 1] != NULL && i < sizeDomain; i++)
					domain[i] = fq_username[pos + i + 1];
				domain[i] = L'\0';
			}
		}
		else
		{
			int i;
			for (i = 0; i < pos && i < sizeUsername; i++)
				username[i] = fq_username[i];
			username[i] = L'\0';
		}
	}

	void WideCharToChar(
		__in PWSTR data,
		__in int buffSize,
		__out char *pc
	)
	{
		WideCharToMultiByte(
			CP_ACP,
			0,
			data,
			-1,
			pc,
			buffSize,
			NULL,
			NULL);
	}

	void CharToWideChar(
		__in char* data,
		__in int buffSize,
		__out PWSTR pc
	)
	{
		MultiByteToWideChar(
			CP_ACP,
			0,
			data,
			-1,
			pc,
			buffSize);
	}

	size_t iso8859_1_to_utf8(char *content, size_t max_size)
	{
		char *src, *dst;

		//first run to see if there's enough space for the new bytes
		for (src = dst = content; *src; src++, dst++)
		{
			if (*src & 0x80)
			{
				// If the high bit is set in the ISO-8859-1 representation, then
				// the UTF-8 representation requires two bytes (one more than usual).
				++dst;
			}
		}

		if (dst - content + 1 > (signed)max_size)
		{
			// Inform caller of the space required
			return dst - content + 1;
		}

		while (dst > src)
		{
			if (*src & 0x80)
			{
				*dst-- = 0x80 | (*src & 0x3f);                     // trailing byte
				*dst-- = 0xc0 | (*((unsigned char *)src--) >> 6);  // leading byte
			}
			else
			{
				*dst-- = *src--;
			}
		}
		return 0;  // SUCCESS
	}

} // Namespace Helper