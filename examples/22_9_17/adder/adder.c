#include <stdio.h>	// for printf()
			// include predefined functions for standard i/o
#include <stdlib.h>	// for atoi()

// define entry point of program
int main(int argc, char* args[])
{
	// get input
	int a = atoi(args[1]);
	int b = atoi(args[2]);

	// process input
	int c = a + b;

	// output result
	printf("sum: %d\n", c);

	// exit program
	return 0;
}	
