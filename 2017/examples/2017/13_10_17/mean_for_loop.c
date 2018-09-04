#include <stdio.h>

int main()
{
	int numbers[5] = {5, 2, 1, 4, 5}; 	// declare and init array of a bunch of nums
	int total = 0;				// temp var for holding sum of al array elems

	for (int i = 0; i < 5; i = i + 1)	// loop for i = 0, until y > 4, increment i each iteration
	{
		total = total + numbers[i];	// accumulate number elem value in total
	}	

	printf("Average is %f\n", total / 5.0);	// average is the total divided by the number of elems (5)

	return 0;
}
