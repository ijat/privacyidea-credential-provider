/* * * * * * * * * * * * * * * * * * * * *
**
** Copyright 2019 Nils Behlen
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
** * * * * * * * * * * * * * * * * * * */

#pragma once
#include <string>
#include <codecvt>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define DbgRelPrintLn(message) Logger::Get().log(message, __FILENAME__, __LINE__, true)
#define DebugPrintLn(message) Logger::Get().log(message, __FILENAME__, __LINE__, false)

class Logger
{
public:
	Logger(Logger const&) = delete;
	void operator=(Logger const&) = delete;

	static Logger& Get() {
		static Logger instance;
		return instance;
	}

	void log(const char* message, const char* file, int line, bool logInProduction);

	void log(const wchar_t* message, const char* file, int line, bool logInProduction);

	void log(int message, const char* file, int line, bool logInProduction);

	void log(std::string message, const char* file, int line, bool logInProduction);

	void log(std::wstring message, const char* file, int line, bool logInProduction);

private:
	Logger();

	void logS(std::string message, const char* file, int line, bool logInProduction);

	void logW(std::wstring message, const char* file, int line, bool logInProduction);

	bool releaseLog;

	std::string logfilePathDebug = "C:\\privacyIDEACPDebugLog.txt";
	std::string logfilePathProduction = "C:\\privacyIDEACredentialProviderLog.txt";
};
