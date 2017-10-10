#include <stdio.h>
#include <stdlib.h>

int main()
{
	// watch out, random number will always be the same random number. one must seed the generator
	int random_numbr = rand();

	printf("Random number is: %d\n", random_numbr);
	return 0;
}
