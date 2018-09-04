#include <stdio.h>

int min(int i, int j)
{
	if (i < j) 
	{
		return i;
	}
	else
	{
		return j;
	}
}

int main()
{
	printf("The minimum of 3 and 10 is %d", min(3, 10));
	printf("The minimum of 220 and -12 is %d", min(220, -12));
	return 0;
}
