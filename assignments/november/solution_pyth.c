#include <stdio.h>
#include <math.h>

int main()
{
	char a, b, c;
	printf("Input side a: ");
	a = getchar();
	getchar(); 
	printf("Input side b: "); 

	b = getchar(); 

	c = sqrt(a * a + b * b);
	printf("Side c is of length: %d", c); 


	return 0; 
}
