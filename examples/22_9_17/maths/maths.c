#include <stdio.h>

// WARNING: must link the math library with `gcc maths.c -lm`
// otherwise will get undefined references
#include <math.h>

// entry point
int main()
{
	// declare and initialize input number
	float num1 = 234.444;

	// declare variable to hold an average later on
	float avg;

	// print the square root of num1
	printf("The square root of %.1f is %.1f\n", num1, sqrt(num1)); 
	
	// print the square of num1
	printf("%.1f squared is %.1f\n", num1, pow(num1, 2));

	// compute the average of the square root and the square of num1
	// (sqrt(num1) + num1^2)/2 
	avg = (sqrt(num1) + pow(num1, 2)) / 2;

	// print the result
	printf("\nThe average of the square root and the square of %.1f is: %.1f\n", num1, avg);

	// exit program gracefully
	return 0; 
}


