#include <stdio.h>

int square (int num)
{
	int tmp = num * num;
	return tmp;
}

int main()
{
	int c = 1; 
	while (c <= 12)
	{
		printf("%d squared is %d\n", c, square(c)); 
		c++; 
	}
	return 0;
}
