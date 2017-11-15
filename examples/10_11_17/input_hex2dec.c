#include <stdio.h>

int main()
{
	int inputnum; 
	printf("Input a hex number to convert: "); 
	if (scanf("%x", &inputnum) == 0)
	{
		printf("uh oh, please input an integer\n"); 
		return -1;
	}
	printf("Your hex input, 0x%x, is %d in decimal\n", inputnum, inputnum); 
	return 0;
}
