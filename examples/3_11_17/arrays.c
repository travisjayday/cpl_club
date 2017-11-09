#include <stdio.h>

int main ()
{
	// declare and initialize an array of floats
	float values[6] = { 2.2, 3.0, 1.5, 1.8, 2.2, 3.3 };

	// assign the first element to 9.2
	values[0] = 9.2; 

	// assign the second element to 5.0
	values[5] = 5.0; 

	// total will be the sum of all elements of the array values
	float total = 0; 

	printf("The array is defined as: \nE| V\n"); 

	// loop from i = 0, until i == 6, and increment i for each iteration
	for (int i = 0; i < 6; i++)
	{
		// print the value of the element at the current index
		printf("%d: %f\n", i, values[i]);

		// accumulate in the total the values at element of values at i
		// such that 
		// 	total = total + values[0];
		// 	total = total + values[1];
		// 	...   = ...   + ...      ; 
		// 	total = total + values[5]; 
		total = total + values[i]; 
	}

	printf("The average of all values is %f\n", total / 6.0); 
	return 0;
}
