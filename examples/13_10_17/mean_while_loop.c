#include <stdio.h>

int main()
{
	int numbers[5] = {5, 2, 1, 4, 5}; 	// declare and init array of a bunch of nums
	int total = 0;				// temp var for holding sum of al array elems

	int counter = 0;
	while (counter < 5)
	{
		total = total + numbers[counter];	// accumulate number elem value in total
		counter = counter + 1; 
	}	

	printf("Average is %f\n", (float)total / 5.0);	// average is the total divided by the number of elems (5)

	return 0;
}
