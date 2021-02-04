#include<iostream>
#include<sys/utsname.h>
#include<string>
#include<stdlib.h>
#include "program1.h"

/********************************************************************
 * File: program1.cpp
 * Author: Mork
 * Procedures:
 * program1	- output information about the system using uname(1) 
 			and uname(2)
********************************************************************/

/*******************************************************************
 * std::string program1()
 * Author: Mork
 * Date: 13 September 2020
 * Description: output information about the system using uname(1) 
 * 			and uname(2)
 *
 * Parameters: None
*******************************************************************/
std::string program1() {
	
	std::string sysInfo=""; // helper string for uname(2)

	struct utsname buffer;  // declare buffer as a utsname for uname

	uname(&buffer);         // buffer to point to struct

	// use uname(2) to find system information
	sysInfo += "Using uname(2) from the 'uname(2) - Linux man page'\n\n";
	
	// system name information
	sysInfo += "system name = ";
	sysInfo += buffer.sysname;
	sysInfo += "\n";
	// node name information
	sysInfo += "node name   = ";
	sysInfo += buffer.nodename;
	sysInfo += "\n";
        // release information
	sysInfo += "release     = ";
	sysInfo += buffer.release;
	sysInfo += "\n";
        // version information
	sysInfo += "version     = ";
	sysInfo += buffer.version;
	sysInfo += "\n";
        // machine information
	sysInfo += "machine     = ";
	sysInfo += buffer.machine;
	sysInfo += "\n";
        // domain information
	sysInfo += "domain name = ";
	sysInfo += buffer.domainname;
	sysInfo += "\n";

	// use uname(1) now
	std::cout << "Using uname(1) from the 'uname(1) - Linux man page'" 
		<< "\n\n";
	
	// call uname(1) through a system call.
	std::cout << "output of 'uname -a'\n";
	system("uname -a");                    // output uname(1) information
	std::cout <<"\n\n";

        // return the string that has the uname(2) information.
	return sysInfo;
}

