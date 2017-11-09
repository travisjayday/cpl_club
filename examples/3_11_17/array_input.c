#include <stdio.h>

int main()
{
	char data[10]; 
	printf("Enter 10 data points:");
	for (int i = 0; i < 10; i++)
	{
		data[i] = getchar(); 
	}

	return 0; 
}
