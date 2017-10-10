#include <stdio.h>

int main()
{
	int base, exponent, result;

	base = 2;
	exponent = 5;
	result = 1;

	while (exponent > 0)
	{
		result = result * base; 
		exponent = exponent -1;
	}

	printf("solution is %d\n", result);
}
