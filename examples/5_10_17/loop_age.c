#include <stdio.h>

int main()
{
	int age = 2;

	while (age < 30) 
	{
		if (age > 18)
		{
			printf("%d: You are a grwon up\n", age);
		}
		else if (age <= 10)
		{
			printf("%d: You are just a kid\n", age);
		}
		else
		{
			printf("%d: You like playing cod\n", age);
		}
		age = age + 1;   
	}

	printf("%d: You died of eye strain\n", age);
	return 0;
}	
