#include <stdio.h>

int main()
{
	char times = 0; 
	printf("How many times [0-9] do you want to print 'hello'?: "); 
	times = getchar(); 
	
	// watch out because ascii code is gonna be large
	while (times != 0) 
	{
		printf("hello\n"); 
		times = times - 1; 
	}

	return 0; 
}
