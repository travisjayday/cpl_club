#include <stdio.h>

int main()
{
	float base = 2.0;
	float result = 1.0;

	for (int x = 5; x > 0; x--)
		result *= base; 

	printf("solution is %f\n", result);
}
