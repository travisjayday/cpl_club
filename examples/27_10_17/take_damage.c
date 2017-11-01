#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int print_random_num()
{
	int random_num = rand(); 
	printf("The random number is %d\n", random_num); 	

}

int main()
{
	srand(time(NULL)); 
	print_random_num(); 
	print_random_num(); 
	print_random_num(); 

/*	for (int i = 0; i < 10; i++)
	{
		
	}*/
	return 0;
}
