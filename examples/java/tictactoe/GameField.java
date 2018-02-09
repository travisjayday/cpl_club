// class that represents the 3by3 game field
public class GameField {

	// arary that will hold characters representing each of the 9 fields
	char[] data; 

	// Constructor is called when `new GameField()` is called
	GameField() { 
		// allocate 9 characters for the array
		data = new char[9]; 

		// initialize the data to ' ' space character
		for (int i = 0; i < data.length; i++)
			data[i] = ' ';
	}

	// method to print the game field to screen	
	void printField() { 
		// clear screen
		System.out.print("\n\n\n\n\n\n\n\n\n\n"); 

		// print field
		System.out.println("-------------");
		System.out.println("| " + data[0] + " | " + data[1] + " | " + data [2] + " |"); 
		System.out.println("-------------");
		System.out.println("| " + data[3] + " | " + data[4] + " | " + data [5] + " |");
		System.out.println("-------------");
		System.out.println("| " + data[6] + " | " + data[7] + " | " + data [8] + " |");
		System.out.println("-------------");
	}
	
	// sets the character in data array either to 'X' at row: r, column: c, w or 'O'
	void setSquare(int r, int c, boolean cross) {
		// for each row, increase index by 3, add 1 for column offset
		data[r * 3 + c] = cross? 'X' : 'O'; 
	}
	
	// returns the character at field position r,c
	char getSquare(int r, int c) {
		return data[r * 3 + c]; 
	}
	
	// determine patterns in the field
	boolean evalField() { 
		// loop r from 0 to 1
		for (int r = 0; r < 2; r++) {
			if (getSquare(r, 0) != ' ' && 
				getSquare(r, 0) == getSquare(r, 1) && 
				getSquare(r, 0) == getSquare(r, 2)) {
				// check rows
				System.out.println("Winner is: " + getSquare(r, 0));
				return true;
			}
			if (getSquare(0, r) != ' ' && 
					getSquare(0, r) == getSquare(1, r) && 
					getSquare(0, r) == getSquare(2, r)) {
				// check columns
				System.out.println("Winner is: " + getSquare(0, r));
				return true;
			}
		}
		if (getSquare(1, 1) != ' ' &&  
				((getSquare(0, 0) == getSquare(1, 1) && getSquare(0, 0) == getSquare(2, 2)) ||
				getSquare(0, 2) == getSquare(1, 1) && getSquare(0, 2) == getSquare(2, 0))) {
			// check diogonal 
			System.out.println("Winner is: " + getSquare(1, 1));
			return true; 
		}
		return false;
	}
}
