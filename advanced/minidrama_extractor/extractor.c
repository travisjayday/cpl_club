#include <stdio.h>				// include for standard input output
#include <stdlib.h>				// include for system()
#include <string.h>				// include for memcpy() and memcmp()

#define BUFFER_SIZE 10000			// preprocessor define max buffer size of 10000 characters

/* Entry Point */ 
int main(int argc, char* args[])
{
	char* input = "Travis\0"; 		// default input value (searching for input)		
	const char EOI = '@';			// end of input character, denoting the end of the input
	char inbuffer[BUFFER_SIZE];		// input buffer (text given by user)
	char outbuffer[BUFFER_SIZE];		// output buffer (lines found)
	char input_len = strlen(input) -1;	// computed length of (searching input) 

	if (argc != 1)				// if argument was specified
		input = args[1]; 		// set search input to the specifed argument

	printf(
	"Searching for '%s' lines.\n\
Run `./a.out yourname` for other names.\n\
Paste the minidrama below, then type the %c symbol, then [enter]. \n\
-----------------------------------------------\n", input, EOI); 
	
	char c; 				// temp character var for loop
	int i = 0;				// i will be length of minidrama (in chars) 
	for (; (c = getchar()) != EOI; i++)	// loop until end char reached
		inbuffer[i] = c;		// copy input character by character


	int j = 0, o = 0;			// looping vars; j = index in inbuffer, o = index in outbuffer	
       	for (; j < i; )	 			// loop through whole input buffer
	{
		int line_len = 0;		// used to temp store line length
		while (inbuffer[j] != '\n')	// loop until end of line 
		{
			line_len++;		// increment line length
			j++;			// and incremenet inbuffer index
		}
		j -= line_len; 

		char s; 			// s will be the index (from start of line) of the ')' character
		for (s = 0; s < line_len; s++)
		{
		  	if (inbuffer[j + s] == ')') 
				break;	
		}
		s++; 


		if (memcmp(inbuffer + j, input, input_len) == 0) 	// if start of line + index of ) is equal to input
		{
			memcpy(outbuffer + o, inbuffer + j, line_len+1); 	// copy the line + newline to outbuffer
			o += line_len +1; 					// update output index (accomodate for new chars)
		}
		j += line_len +1;
	}

	system("clear"); 						// issue linux system command to clear screen

	printf("Should I write output to a file? (y/n): ");		// prompt user to decide to write fo file or not
fflush(stdout);	

	char toFile;							// temp var for user input (eat the newline)

	while (getchar() != '\n');					// handle annoying newlines
	toFile = getchar();						// get char from user
		
	while (!(toFile == 'y' || toFile == 'n'))			// loop until user writes y or n
	{
		printf("Invalid input!"); 				// if user specifed wrong input
		scanf(" %c", &toFile);
	}
	
	
	if (toFile == 'y')						// print file selectd
	{
		FILE *outfile = fopen("mini_drama.txt", "w");		// open file to print to
		if (outfile == NULL)					// check if opened succcessfuly
		{
			printf("Error: failed to write to file!\n");	// if not, throw error
			return -1;					// exit with -1
		}
		fprintf(outfile, "%s", outbuffer);			// if it was successful, print to file
		printf("Wrote to file mini_drama.txt succesfully\n");	
	}
	else
	{
		system("clear");					// clear screen again
		printf("Output: \n%s\n", outbuffer);			// print the output to the screen
	}
	return 0;
}
