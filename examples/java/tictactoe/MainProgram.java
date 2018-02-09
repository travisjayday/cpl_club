import java.util.Scanner;

// driver class: program starts here at main
public class MainProgram {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		// boolean to keep track of whose turn it is
		boolean crossTurn = false; 
		
		// Declare and Instantiate a Scanner class called reader; used to get user input
		Scanner reader = new Scanner(System.in);

		// Declare and Instantiate a GameField that holds all kinds of useful methods for tic tac toe
		GameField mGameField = new GameField(); 
		
		// loop until evalField() returns true. evalField() returns true if and only if 
		// 3 x's or 3 o's have been placed in a row, column, or diagonal.
		while (!mGameField.evalField()) {

			// print the field to screen
			mGameField.printField(); 
			
			
			// if it's cross's turn, prompt cross to input data
			if (crossTurn)
				System.out.print("Cross Turn: "); 
			// if it's not cross's turn, prompt circle to input data
			else
				System.out.print("Circle Turn: "); 
			
			// get the next two integers that are typed into the terminal (separated by spaces)
			// for example, if the input is "   0 1  ", row will be 0, and col will be 1
			int row = reader.nextInt(); 
			int col = reader.nextInt(); 
			
			// check if the input is out of range. If it is, try again to get new input
			while (row > 2 || col > 2) { 
				System.out.println("Error: invalid position. Try again: ");
				row = reader.nextInt();
				col = reader.nextInt(); 
			}
			
			// check if the selected field is still empty; if it's not empty, user must input again
			while (mGameField.getSquare(row, col) != ' ') {
				System.out.println("Field already used! Try again: "); 
				row = reader.nextInt();
				col = reader.nextInt(); 
			}

			// finally mark the square
			mGameField.setSquare(row, col, crossTurn);
			
			// and print the new field
			mGameField.printField(); 
			
			// switch turns
			crossTurn = !crossTurn; 
		} 
	}

}
