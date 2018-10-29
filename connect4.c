/* ENGGEN131 Project - C Project - 2018 */
/* Connect Four */

#include "connect4.h"

/*
*** Xiaobin Lin ######### ***
This is the file that you will be submitting for marking
Complete the definitions of the functions in this file
DO NOT REMOVE ANY FUNCTION DEFINITIONS - they all must be present when you submit this file
*/

typedef struct {
	int row;
	int col;
	int dumbmove;
} Move;

/*********************************************************************************/
/*
This function sorts an array using bubble sort
*/
void SortArray(double array[], int length) {
	// Sort the array using bubble sort
	for (int i = 0; i < length; i++) {
		for (int j = i + 1; j < length; j++) {
			if (array[i] > array[j]) {
				// Swap two values without using temp variable
				array[i] = array[i] + array[j];
				array[j] = array[i] - array[j];
				array[i] = array[i] - array[j];
			}
		}
	}
	return;
}

/*********************************************************************************/
/*
This function calculates the result of a number raised to a power
*/
int ToThePowerOf(int num, int toThePowerOf) {
	int result = num;
	if (toThePowerOf == 0) {
		return 1;
	}
	for (int i = 1; i < toThePowerOf; i++) {
		result = result * num;
	}
	return result;
}

/*********************************************************************************/
/*
This function finds the middle value given three values
*/
int SecondPlacePrize(int prize1, int prize2, int prize3)
{
	// Sort the array and return the middle value
	double array[3];
	array[0] = prize1;
	array[1] = prize2;
	array[2] = prize3;
	SortArray(array, 3);
	return ((int)array[1]);
}

/*********************************************************************************/
/*
This function returns true if there are 4 consecutive characters in an array
*/
int FourInARow(int values[], int length)
{
	int counter = 0;
	int previousValue = values[0];

	for (int i = 1; i < length; i++) {
		if (previousValue == values[i]) {
			counter++;
		}
		else {
			// Reset the counter if the current value is not the same as 
			// previous value
			counter = 1;
			previousValue = values[i];
		}
		if (counter == 4) {
			// Return the index of the first occurrence 
			return i - 3;
		}
	}
	// Not found
	return -1;
}

/*********************************************************************************/
/*
This function converts binary to decimal
*/
int BinaryToDecimal(int binary)
{
	int power = 0;
	int rem;
	int result = 0;
	while (binary != 0) {
		// Converting binary to decimal using method taught in 131 and 101
		rem = binary % 10;
		result = result + ToThePowerOf(2, power) * rem;
		binary = binary / 10;
		power++;
	}
	return result;
}

/*********************************************************************************/
/*
This function finds the median of an array
*/
double MedianAbility(double abilities[], int length)
{
	// Sort the list first
	SortArray(abilities, length);

	// Find the middle the array
	if (length % 2 == 0) {
		int middle = length / 2;
		return (abilities[middle - 1] + abilities[middle]) / 2;
	}
	else {
		return abilities[length / 2];
	}
}

/*********************************************************************************/
/*
This function appends a character to string
*/
void AppendCharToString(char *string, char c) {
	int length = (int)strlen(string);
	string[length] = c;
	string[length + 1] = '\0';
}

/*********************************************************************************/
/*
This function remove consecutive spaces 
*/
void RemoveSpaces(char *name)
{
	int length = (int)strlen(name);
	// Allocate memory for final string, add one in the end for \0
	char* finalString = (char*)malloc((length + 1) * sizeof(char));
	finalString[0] = '\0';
	char previousChar = '\0';
	for (int i = 0; i < length; i++) {
		if (previousChar == ' ' && name[i] == ' ') {
			// Do nothing
			;
		}
		else {
			AppendCharToString(finalString, name[i]);
			previousChar = name[i];
		}
	}

	for (int i = 0; i < length; i++) {
		name[i] = finalString[i];
	}
}


/*********************************************************************************/
/*
This function sets up the board with all zeros and adds an obstacle at the center of the board 
*/
void InitialiseBoard(int board[MAX_SIZE][MAX_SIZE], int size)
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			// Set the whole board to 0
			board[i][j] = 0;
		}
	}

	if (size % 2 != 0) {
		// Make the middle of the board an obstacle 
		board[size / 2][size / 2] = 3;
	}
	else {
		int index = size / 2 - 1;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				// Make the middle of the board an obstacle 
				board[index + i][index + j] = 3;
			}
		}
	}
}

/*********************************************************************************/
/*
This function check if there is an obstacle in the row and column specified
*/
int CheckObstacle(int board[MAX_SIZE][MAX_SIZE], int row, int col) {
	if (board[row][col] == 0) {
		// No obstacle
		return 0;
	}
	else {
		// Obstacle present
		return 1;
	}
}

/*********************************************************************************/
/*
This function finds the row and col to place the token given a side and a move by 
mean of propagation 
*/
Move CodeToMove(int board[MAX_SIZE][MAX_SIZE], int size, char side, int move) {
	int currentRow = -1;
	int currentCol = -1;
	int dumbMove = 0;
	int obstacle = 0;
	Move movement;

	// Increase one step at a time until it sees an obstacle
	if (side == 'N') {
		currentRow = 0;
		currentCol = move;
		dumbMove = CheckObstacle(board, currentRow, currentCol);
		while (obstacle == 0 && currentRow != size - 1) {
			currentRow++;
			obstacle = CheckObstacle(board, currentRow, currentCol);
			if (obstacle == 1) {
				// Go back one step where there is no obstacle
				currentRow--;
			}
		}
	}
	else if (side == 'S') {
		currentRow = size - 1;
		currentCol = move;
		dumbMove = CheckObstacle(board, currentRow, currentCol);
		while (obstacle == 0 && currentRow != 0) {
			currentRow--;
			obstacle = CheckObstacle(board, currentRow, currentCol);
			if (obstacle == 1) {
				// Go back one step where there is no obstacle
				currentRow++;
			}
		}
	}
	else if (side == 'W') {
		currentRow = move;
		currentCol = 0;
		dumbMove = CheckObstacle(board, currentRow, currentCol);
		while (obstacle == 0 && currentCol != size - 1) {
			currentCol++;
			obstacle = CheckObstacle(board, currentRow, currentCol);
			if (obstacle == 1) {
				// Go back one step where there is no obstacle
				currentCol--;
			}
		}
	}
	else if (side == 'E') {
		currentRow = move;
		currentCol = size - 1;
		dumbMove = CheckObstacle(board, currentRow, currentCol);
		while (obstacle == 0 && currentCol != 0) {
			currentCol--;
			obstacle = CheckObstacle(board, currentRow, currentCol);
			if (obstacle == 1) {
				// Go back one step where there is no obstacle
				currentCol++;
			}
		}
	}

	movement.row = currentRow;
	movement.col = currentCol;
	movement.dumbmove = dumbMove;
	return movement;
}

/*********************************************************************************/
/*
This function checks if there is any valid move in the board
*/
int IsBoardFull(int board[MAX_SIZE][MAX_SIZE], int size) {
	// The board is considered full when the outer layer is full

	// Check top and bottom
	for (int i = 0; i < size; i++) {
		if (board[0][i] == 0) {
			return 0;
		}
		if (board[size - 1][i] == 0) {
			return 0;
		}
	}

	// Check first and last element of board from 1 to size-1
	for (int i = 1; i < size - 1; i++) {
		if (board[i][0] == 0) {
			return 0;
		}
		if (board[i][size - 1] == 0) {
			return 0;
		}
	}
	return 1;
}

/*********************************************************************************/
/*
This function adds the player's token to the board utilizing CodeToMove function
*/
void AddMoveToBoard(int board[MAX_SIZE][MAX_SIZE], int size, char side, int move, int player, int *lastRow, int *lastCol)
{
	// Move thing
	Move movement = CodeToMove(board, size, side, move);
	int dumbMove = movement.dumbmove;
	int currentRow = movement.row;
	int currentCol = movement.col;

	if (dumbMove == 0) {
		board[currentRow][currentCol] = player;
		*lastRow = currentRow;
		*lastCol = currentCol;
	} else {
		// Dumb move
		*lastRow = -1;
		*lastCol = -1;
	}

}

/*********************************************************************************/
/*
This function finds amount of same player token in one direction 
*/
int PiecePropagate(int board[MAX_SIZE][MAX_SIZE], int x, int y, int stepX, int stepY, int player, int size) {
	int counter = 0;
	while (counter<4) { 
		// Increment the checking index on each iteration
		x = x + stepX;
		y = y + stepY;
		// printf("Checking for PLAYER %i\n", player);
		if (x >= 0 && y >= 0 && x < size && y < size) {
			/* printf("Checking at (%i, %i) \n", x, y);
			printf("Value is %i \n", board[x][y]);
			printf("  Counter at (%i, %i) \n", x, y);  */
			if (board[x][y] == player) {
				counter++;
			} else {
				break;
			}
		} else {
			break;
		}
	}
	return counter;
}

/*********************************************************************************/
/*
This function resets the specified row and col of the board to zero (empty)
*/
void RemovePiece(int board[MAX_SIZE][MAX_SIZE], int row, int col) {
	// Reset the position to 0
	board[row][col] = 0;
	return;
}

/*********************************************************************************/
/*
This function determines if the game is over utilizing PiecePropagation  
*/
int CheckGameOver(int board[MAX_SIZE][MAX_SIZE], int size, int player, int row, int col)
{
	// Return true if one of the following condition is met:
	// 1: Board is full
	// 2: There is a connect 4

	int counter;

	if (row == -1 && col == -1){
		return 0;
	}

	if (IsBoardFull(board, size)) {
		// If the board is full, the player that made the last move won
		return player;
	}

	// The following HEINOUSLY long code is for checking if there is a connect 4
	// The checking method is piece propagation
	// e.g. go to the left of the last piece placed and iteration through until 
	// it sees a non current player token
	// then go to the right

	// Check vertical
	counter = 1;
	counter = counter + PiecePropagate(board, row, col, 1, 0, player, size);
	counter = counter + PiecePropagate(board, row, col, -1, 0, player, size);

	if (counter >= 4) {
		return player;
	}

	// Check horizontal
	counter = 1;
	counter = counter + PiecePropagate(board, row, col, 0, 1, player, size);
	counter = counter + PiecePropagate(board, row, col, 0, -1, player, size);

	if (counter >= 4) {
		return player;
	}

	// Check negative diagonal
	counter = 1;
	counter = counter + PiecePropagate(board, row, col, -1, -1, player, size);
	counter = counter + PiecePropagate(board, row, col, 1, 1, player, size);

	if (counter >= 4) {
		return player;
	}

	// Check positive diagonal
	counter = 1;
	counter = counter + PiecePropagate(board, row, col, 1, -1, player, size);
	counter = counter + PiecePropagate(board, row, col, -1, 1, player, size); 

	if (counter >= 4) {
		return player;
	}

	return 0;
}

/*********************************************************************************/
/*
This formats using a very simple dictionary like structure
Key : Value
0 	: .
1 	: X
2 	: O
3 	: # 
*/
char Num2char(int num) {
	if (num == 0) {
		return '.';
	}
	else if (num == 1) {
		return 'X';
	}
	else if (num == 2) {
		return 'O';
	}
	else if (num == 3) {
		return '#';
	}
	// ERROR
	return 'F';
}

/*********************************************************************************/
/*
This function styles the one line as per request
*/
void BoardStyle(char* boardString, int size, char c) {
	strcat(boardString, "--");
	if (c == '#') {
		for (int i = 0; i < size; i++) {
			AppendCharToString(boardString, (char)i + 48); //Convert integer to ASCII
		}
	}
	else {
		for (int i = 0; i < size; i++) {
			AppendCharToString(boardString, c); //Convert integer to ASCII
		}
	}
	strcat(boardString, "--\n");
}

/*********************************************************************************/
/*
This function styles the board as per request
*/
void GetDisplayBoardString(int board[MAX_SIZE][MAX_SIZE], int size, char *boardString)
{
	char* bufferString = (char*)malloc(100 * sizeof(char));
	boardString[0] = '\0';

	BoardStyle(boardString, size, 'N');
	BoardStyle(boardString, size, '#');

	for (int i = 0; i < size; i++) {
		sprintf(bufferString, "W%i", i);
		strcat(boardString, bufferString);
		for (int j = 0; j < size; j++) {
			AppendCharToString(boardString, Num2char(board[i][j]));
		}
		sprintf(bufferString, "%iE\n", i);
		strcat(boardString, bufferString);
	}

	BoardStyle(boardString, size, '#');
	BoardStyle(boardString, size, 'S');
}

/*********************************************************************************/
/*
This function returns the move that the bot should make using following logic 
1: Find any move that can lead to an instant win
2: If no instant win is found, make a random move
*/
void GetMoveBot1(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	char direction[5] = "NSWE";
	Move movement;
	int check = 0;
	int row = 0;
	int col = 0;

	// Find winning
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < size; j++) {
			movement = CodeToMove(board, size, direction[i], j);

			if (movement.dumbmove == 0) {
				AddMoveToBoard(board, size, direction[i], j, player, &row, &col);
				check = CheckGameOver(board, size, player, row, col);
				RemovePiece(board, movement.row, movement.col);
			}
			if (check == player) {
				// Found winning position
				*side = direction[i];
				*move = j;
				// printf("WINNING MOVE POS: (%c, %i) /n", *side, *move);
				return;
			}
		}
	}

	// Random move
	if (check != player) {
		do {
			int randNum = rand() % 4;
			*side = direction[randNum];
			*move = rand() % size;
			// printf("Direction: %c, move: %i", direction[randNum], *move);
			movement = CodeToMove(board, size, *side, *move);
		} while (movement.dumbmove == 1);
	}

}

/*********************************************************************************/
/*
This function returns the move that the bot should make using following logic 
1: Find any move that can lead to an instant win
2: If no instant win is found, make a random move
*/
void GetMoveBot2(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	char direction[5] = "NSWE";
	Move movement;
	int check = 0;
	int row = 0;
	int col = 0;

	// Find winning move
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < size; j++) {
			movement = CodeToMove(board, size, direction[i], j);
			if (movement.dumbmove == 0) {
				// printf("CHECKING: (%c, %i) \n", direction[i], j);
				AddMoveToBoard(board, size, direction[i], j, player, &row, &col);
				check = CheckGameOver(board, size, player, row, col);
				// printf("REMOVING: (%i, %i) \n", pos.row, pos.col);
				RemovePiece(board, movement.row, movement.col);
			}
			if (check == player) {
				// Found winning position
				*side = direction[i];
				*move = j;
				// printf("WINNING MOVE POS: (%c, %i) /n", *side, *move);
				return;
			}
		}
	}

	// Random move
	if (check != player) {
		do {
			int randNum = rand() % 4;
			*side = direction[randNum];
			*move = rand() % size;
			// printf("Direction: %c, move: %i", direction[randNum], *move);
			movement = CodeToMove(board, size, *side, *move);
		} while (movement.dumbmove == 1);
	}

}
