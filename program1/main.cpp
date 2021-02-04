#include<iostream>
#include<sys/utsname.h>
#include "program1.h"

/**************************************************************************
 * File: main.cpp
 * Author: Mork
 * Procedures:
 * main 	- outputs the function of program1(), which will call uname().
***************************************************************************/

/**************************************************************************
 * int main()
 * Author: Mork
 * Date: 13 September 2020
 * Description: outputs program1(), which will call uname().
 *
 * Parameters: None
***************************************************************************/
int main() {
	
	std::cout << program1(); // call program1 and output it
				 // output should be the output of uname()

	return 0;
}
