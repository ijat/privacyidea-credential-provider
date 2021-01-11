# Version 3.1.0, 2020-09-29

## Features
 * The behavior of the CP and Filter can be modified for each scenario separately (see docs).

## Enhancements

## Fixes
 * Fix missing Submit button upon failure when 2step is enabled.


# Version 3.0.0, 2020-05-28

## Features
 * Support realms by configuring a realm mapping in the registry
 * Support of Push Token
 * Support offline authentication
 * Support exclusion of a single account

## Enhancements

## Fixes


# Version 2.5.2, 2019-08-02

## Fixes
 * Fix for clients experiencing a freeze when using only hide_otp configuration.
 * URL encoding of parameters which are sent to the server.

# Version 2.5.1, 2018-11-26

### Fixes

 * Fix buffer overflow in certain RDP scenarios, that crashes the terminal server client.
 * Make default tile configurable via NO_DEFAULT='1' registry key.


# Version 2.5.0, 2018-10-15

### Features
 *	Support SMS/Email tokens, which require a transaction id to be appended to the request. This only works when the CP is configured to ask for the OTP in a second step.
	The message of the challenge is displayed to the user.
	
### Enhancements
 *	Logging of sensitive data can be activiated by a registry key
 
### Fixes
 *	Fix missing lookup of the domain when using over-the-shoulder-prompting (UAC).
	Note: The UAC scenario with the credential provider does currently not work on Windows 8/ Server 2012.
 
# Version 2.4.0, 2018-09-13

### Features
 *	Password change on a locked workstation is not possible. If this occurs, block our tile and guide the user to sign out and in again to
	complete the password change in the LOGON scenario. (Similar to what Windows does)
	
### Enhancements

### Fixes


# Version 2.3.3, 2018-08-21

### Features
 * Optionally send an empty password or the domain password to the privacyIDEA server.
   (As intended in version 2.0)
   This is only possible if the request for the OTP is made in a second step.

### Enhancements
 * Added icon to display in installed software list
 * Improved debug message format
 * More debug messages
 * Changed version number format to end with buildnumber
 
### Fixes
 * Displaying the correct version number in the MSI as well as in the installed software list
 * Removed unnecessary communication with the privacyIDEA server

# Version 2.3.2, 2018-08-19

### Features
* Support changing the password on logon if the password expired or is requested to change by the admin

### Enhancements

### Fixes


# Version 2.3.1, 2018-07-19

### Features
  * Optional registry key for custom ports

### Enhancements
 * Adjusted Installer

### Fixes
  * Fixed a bug with parsing the path from the URL  

# Version 2.2, 2018-05-29

### Features
* Bugfix for URLs with scheme and paths specified
* Username and domain hideable on locked machines (custom login text will still be displayed)
* Custom OTP field text

### Enhancements
 * Adjusted Installer

### Fixes


# Version 2.1, 2018-05-07

### Features

### Enhancements
  
* When connecting to a machine with privacyIDEA CP, allow
  to use the credentials which were already passed in NLA.
  We only ask for OTP.

### Fixes


# Version 2.0, 2018-05-03

### Features
  * Replaced libcurl and OpenSSL with Winhttp
  * SSL errors can be ignored optionally
  * Second dialog to enter OTP separately
  * Optionally send the domain password to the privacyIDEA server
  
### Enhancements
  * Adjusted Installer
  * Add new logos
  * Cleanup license and README

### Fixes
  * Add correct user-agent
