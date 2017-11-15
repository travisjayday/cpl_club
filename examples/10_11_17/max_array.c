#include <stdio.h>

int print_array(int arr[], int len)
{
	printf("{ "); 
	for (int i = 0; i < len; i++)
	{
		printf("%d, ", arr[i]); 
	}
	printf("}"); 
}

int max(int arr[], int len)
{
	int max = -9999999;
	for (int i = 0; i < len; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}	
	}
	return max; 
}

int main()
{
	int my_arr[] = {2, 3, 9, 88, 1, 2};

	printf("My array is: \n"); 
	print_array(my_arr, 6); 
	printf("\n\n"); 

	int largest = max(my_arr, 6);  
	printf("max element in my array is %d\n", largest);  
	return 0;
}
