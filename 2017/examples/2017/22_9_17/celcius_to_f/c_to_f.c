#include <stdio.h>

int main()
{
	float degree_c = 22.0;
	float degree_f = 9.0 / 5.0 * degree_c + 32.0; 

	printf("%f degrees celcius are %f degrees fahrenheit\n", degree_c, degree_f);
	return 0; 
}
