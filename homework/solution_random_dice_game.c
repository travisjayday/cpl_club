#include <stdio.h>				// include standard input output (for printf())
#include <stdlib.h>				// include stdlib for rand() and srand() functions
#include <time.h>				// include time for getting current time to seed srand

int main()					// entry point of program
{
	srand(time(NULL));			// seed the random generator with current time; seed at beginning of program
	int diceRoll = rand() % 6 + 1; 		// generate random number from 1 to 6

	printf("You rolled a %d\n", diceRoll);	// print the value of the diceroll to screen

	if (diceRoll > 3)			// if diceroll is 4, 5, 6
		printf("You've won the game\n");// print you've won the game
	else
		printf("You are a loser\n");	// print you're a loser

	return 0;				// gracefully exit 
}
