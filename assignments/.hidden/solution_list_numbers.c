#include <stdio.h>

int main()
{
	int c = 2;
	while (c <= 65536)
	{
		printf("%d\n", c);
		c *= 2; 
	}	
	return 0;
}
