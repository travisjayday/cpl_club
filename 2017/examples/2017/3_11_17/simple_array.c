#include <stdio.h>

int main()
{
	// declare array that holds 5 integer elements
	int my_array[5]; 

	my_array[0] = 23; 		// set first element to 23
	my_array[4] = 22; 		// set last element to 22
	my_array[1] = 55; 		// set second element to 55

	// print first and last element
	printf("First element of my_array is %d\n", my_array[0]);
	printf("Last element of my_array is %d\n", my_array[4]);

	// print the third element (which WE HAVENT INITIALIZED! uh oh...)
	printf("Third element of my_array is %d\n", my_array[2]); 

	return 0; 
}
