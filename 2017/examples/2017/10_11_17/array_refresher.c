#include <stdio.h>

int main()
{
	int r2[2] = {2, 3}; // method 1
	int arr_name[4];	// method 2 
   	arr_name[0] = 23; // 1st element of array	

	char rarxd[3] = {'h', 'e', 'y'}; 
	char rarxd2[] = "hey\0"; // equivalant statement`

	rarxd2[0] = 'n';
	printf("%s", rarxd2); 
	return 0; 
}
