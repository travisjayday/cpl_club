#include <stdio.h> 	// for i/o
#include <math.h>	// for sqrt()

/* Program to calculate (-b +- sqrt(b^2 - 4ac)) / (2a) */
int main()
{
	// declare variables
	float a, b, c, disc, x1, x2;

	// initialize input variables
	a = 2;
	b = 8;
	c = 2;

	// process input and compute results
	disc = b * b - 4 * a * c;		// calculate discriminant
	x1 = (-b + sqrt(disc)) / (2 * a);	// calculate solution 1
	x2 = (-b - sqrt(disc)) / (2 * a); 	// calculate solution 2

	// print output
	printf("Solution1: %f, Solution2: %f\n", x1, x2);

	// terminate gracefully
	return 0;
}
