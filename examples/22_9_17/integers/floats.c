#include <stdio.h>

// entry point of program 
int main()
{
	/****************************************************************/
	/* objective:                                                   */
	/* solve for y in the linear equation y = 4.5x + 3.2 if x = 5	*/
	/****************************************************************/

	// declare and initialize variables
	float y = 0.0;	 		// declare whole number variables x and y, and initialize
	float x = 0.0; 			// them to 0

	x = 5.0;			// assign x the value of 5

	y = 4.5 * x + 3.2;		// y = 4.5 times x plus 3.2  (PEMDAS applies) 
					// after this statement y holds the value 4 * 5 + 3
					// y is now equal to 23

	// print and format the result
	// %d is a placeholder for an integer (discrete) variable which is specified
	// after the string's finishing quote. 
	
	printf("In the equation `y = 4.5x + 3.2`, for x = 5, y = %f\n\n\n", y);

	// terminate the program gracefully
	return 0;
}
