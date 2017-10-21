#include <stdio.h>
#include <stdlib.h>

int main()
{
	while (1) 
	{
		char random_c = rand() % 128;
		printf("%c", random_c);
	}	
	return 0;
}
