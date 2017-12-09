#include <stdio.h>

int main()
{
	printf("Input an expression using +, -, *, /, %%\n"); 

	float arg1, arg2;
	char operator; 
	scanf("%f %c %f", &arg1, &operator, &arg2); 

	switch (operator)
	{
		case '+':
			printf("%.1f + %.1f = %.1f\n", arg1, arg2, arg1 + arg2); 
			break;
		case '-':
			printf("%.1f - %.1f = %.1f\n", arg1, arg2, arg1 - arg2); 
			break;
		case '/':
			printf("%.1f / %.1f = %.1f\n", arg1, arg2, arg1 / arg2); 
			break;
		case '*':
			printf("%.1f * %.1f = %.1f\n", arg1, arg2, arg1 * arg2); 
			break;
		case '%':
			printf("%d %% %d = %d\n", (int)arg1, (int)arg2, (int)arg1 % (int)arg2); 
	}

	return 0; 
}
