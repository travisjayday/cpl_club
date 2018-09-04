#include <stdio.h>

int main()
{
	int myint = 23;
	float myfloat = 22.2;
	char mychar = 'A'; 
	long long mylong = 9223372036854775807; 
	
	printf("------------Sizes---------------------------------\n"); 
	printf("The size of myint (integer) is \t\t%d bytes\n", sizeof(myint)); 
	printf("The size of myfloat (float) float is \t%d bytes\n", sizeof(myfloat));
	printf("The size of mychar (char) is \t\t%d bytes\n", sizeof(mychar)); 
	printf("The size of mylong (long long) is \t%d bytes\n", sizeof(mylong)); 

	printf("----------Locations-------------------------------\n");
	printf("myint is located at address  \t\t0x%x\n", &myint);
	printf("myfloat is located at address \t\t0x%x\n", &myfloat);
	printf("mychar is located at address \t\t0x%x\n", &mychar);
	printf("mylong is located at address \t\t0x%x\n", &mylong);

	return 0;
}
