#include <stdio.h> 	// tells the compiler to include pre-defined functions
			// from the "standard input output" libarary. This 
			// enables us to use `printf()`

int main()		// this is the header of the function main(). main is
{			// always the `entry point` of a program, e.g. your 
			// program starts here. 

	system("clear");		// executes the system command `clear`
					// this command clears the screen 

	printf("\n\nhello world\n\n");	// printf prints characters to the 
					// screen. A string literal in C is 
					// written in "". The \n is a single 
					// character that represents a newline
					// e.g. like the enter key
	
	return 0; 			// this is the termination point of our
					// program. The `return` keyword exits
					// the function `main` and 0 is the 
					// return value. `0` means that the
					// program terminated successfully	
}
