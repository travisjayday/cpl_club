#include <stdio.h>

#define PASS_LEN 6
#define BUFFER_LEN 20

// definition of str_equal. This function compares two strings for len characters
int str_equal(char str1[], char str2[], int len)
{
	for (int i = 0; i < len; i++)
	{
		if (str1[i] != str2[i])
		{
			return 0; 
		}
	}
	return 1; 
}

int main()
{
	printf("What's the password, bub: ");
	char pass[PASS_LEN] = "secret"; 
	char input[BUFFER_LEN]; 

	scanf("%s", input); 
	if (str_equal(input, pass, PASS_LEN)) 
	{
		printf("Access Granted. Welcome.");
	}
	else
	{
		printf("Halt! You have commited crimes against Linux and its users!");
	}

}
