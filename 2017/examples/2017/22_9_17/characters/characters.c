#include <stdio.h>

int main()
{
	// char holds values from -128 to +127
	char capital_a = 'A';		// this is equal to capital_a = 65 
	char capital_b = 'B'; 		// this is equal to capital_b = 66
	char sum; 

	printf("The ascii value of capital_a is %d\n", capital_a);
	printf("The ascii value of capital_b is %d\n", capital_b);

	printf("\nBut the character representation is: %c and %c\n", capital_a, capital_b);
}
