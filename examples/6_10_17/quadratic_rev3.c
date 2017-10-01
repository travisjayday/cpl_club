#include <stdio.h> 	// for i/o
#include <math.h>	// for sqrt()

/* Program to calculate (-b +- sqrt(b^2 - 4ac)) / (2a) */
int main()
{
	// declare variables
	float a, b, c, disc, x1, x2;

	// initialize input variables
	printf("Define a, b, and c respectfully: ");
	scanf("%f %f %f", &a, &b, &c);

	// process input and compute results
	disc = b * b - 4 * a * c;			// calculate discriminant

	// check IF discriminant LESS THAN 0 
	if (disc < 0)
	{
		// if it is < 0, print "no solutions"
		printf("No real solutions!\n");

		// and terminate the program eaerly
		return -1;
	}

	// else calculate solutions normally		
	x1 = (-b + sqrt(disc)) / (2 * a);
	x2 = (-b - sqrt(disc)) / (2 * a); 

	// print output
	printf("Solution1: %f, Solution2: %f\n", x1, x2);

	// terminate gracefully
	return 0;
}
