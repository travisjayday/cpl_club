#include <stdio.h>

int main()
{
	// objective: solve for y in the linear equation y = 4x + 3 if x = 5

	// declare variables
	int y = 0;	 		// declare whole number variables x and y, and initialize
	int x = 0; 			// them to 0

	x = 5; 				// assign x the value of 5

	y = 4 * x + 3; 			// y = 4 times x plus 3  (PEMDAS applies) 
					// after this statement y holds the value 4 * 5 + 3
					// y is now equal to 23

	// print and format the result
	// %d is a placeholder for an integer variable which is specified
	// after the string's finishing quote. 
	
	printf("In the equation `y = 4x + 3`, for x = 5, y = %d\n", y);

	// terminate the program gracefully
	return 0;
}
