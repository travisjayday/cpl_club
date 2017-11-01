#include <stdio.h>

int main()
{
	printf("Type in 3 characters: "); 
	
	char c1, c2, c3; 
	c1 = getchar(); 
	c2 = getchar();
	c3 = getchar(); 

	printf("You wrote %c%c%c\n", c1, c2, c3); 
	return 0; 
}
