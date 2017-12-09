#include <stdio.h>

int main()
{
	printf("hex : d : c\n"); 
	int i; 
	for (i = 0; i < 128; i++)
	{
		printf("0x%x : %c : %d\n", i, i, i); 
	}
	return 0;
}
