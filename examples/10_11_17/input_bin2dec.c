#include <stdio.h>
#include <math.h>

int main()
{
	/* version 1 
	int bits[8]; 
	printf("Enter a byte: ");
	for (int i = 0; i < 8; i++)
	{
		char bit = getchar();
		bits[i] = bit - '0'; 
	}
	int decimal = 0; 
	for (int i = 7; i >= 0; i--)
	{
		if (bits[i] == 1)
		{
			decimal += pow(2, 7 -i); 
		}	
	}
	printf("decimal: %d", decimal); 
	*/
	
	char c;
	int place = 0; 
	int decimal = 0; 
	while (1)
	{
		c = getchar(); 

		if (c == '1')
		{
			decimal += pow(2, place); 
		}
		else if (c == '\n')
		{
			break;
		}
		else if (c != '0')
		{
			printf("Fatal error"); 
			return -1;	
		}

		place++; 
	}
	printf("decimal: %d", decimal); 
	return 0;
}
