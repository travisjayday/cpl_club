#include <stdio.h>

int main()
{
	char name[8] = "Travis\n\0";
	char *name2 = "john";

	name[0] = 't';

	printf("Your name is %s; ya boy is %s", name, name2);
	return 0;
}
