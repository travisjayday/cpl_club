#include <stdio.h>
#include <stdlib.h>

int main()
{
	char j; 					// random character temp
	int c = 1;					// question number count

	printf("PSAT answers: \n"); 
	printf("------------- \n"); 
	while (c < 25)				// while question count is less than 25, do the following
	{
		j = 'A' + rand() % 4;	// assign j to a random character from 'A' to 'D'
		printf("%d): %c\n", c, j);	// print question number and answer
		c++; 					// increment question count
	}

	return 1;					// gracefully terminate
}
