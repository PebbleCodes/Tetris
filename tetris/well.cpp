/*
@file		well.cpp
@author		Mark Stone
@version	1.0
The header file for well implementation
*/

#include <iostream>
#include "well.h"

using namespace std;

Well::Well(int height, int width) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			board[i][j] = ' ';
		}
	}
}

bool Well::rowIsFull(int row) {
	int counter = 0;
	for (int i = 0; i < WIDTH; i++) {
		if (board[row][i] != ' ') {
			counter++;
		}
	}
	if (counter == 8) {
		return true;
	}
	else {
		return false;
	}
}

void Well::moveRowsDown(int firstRowToMove) {
	for (int i = firstRowToMove; i > 0; i--) {
		for (int j = 0; j < WIDTH; j++) {
			board[i][j] = board[i - 1][j];
		}
	}
	for (int k = 0; k < WIDTH; k++)
		board[0][k] = ' ';
}
//---------------------------------------------
//accessors
bool Well::tetriminoFit(Tetrimino* myTetrimino) {
	Location localLocation;
	int localGrid[SIZE][SIZE];
	localLocation.row = myTetrimino->getLocation().row;
	localLocation.col = myTetrimino->getLocation().col;

	myTetrimino->getGrid(localGrid);
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (localGrid[i][j] == 1) {
				if (localLocation.row + i > HEIGHT - 1) {
					return false;
				}
				else if (localLocation.col + j < 0) {
					return false;
				}
				else if (localLocation.col + j > WIDTH - 1) {
					return false;
				}
				else if (board[localLocation.row + i][localLocation.col + j] != ' ' && localLocation.row + i >= 0 && localLocation.col + j >= 0) {
					return false;
				}
			}
		}
	}
	return true;
}

bool Well::topReached() {
	int counter = 0;
	for (int i = 0; i < WIDTH; i++) {
		if (board[0][i] != ' ') {
			counter++;
		}
	}
	if (counter > 0) {
		return true;
	}
	else {
		return false;
	}
}

void Well::getBoard(char myGrid[][8]) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			myGrid[i][j] = board[i][j];
		}
	}
}

//============================================
//test routines
void Well::makeTestBoard() {

	// make an array of test data for the board
	//	- it has a block in the top row to enable me to test the topReached function
	//	- it has a couple of full rows to enable me to test the clearFullRows function
	char data[HEIGHT][WIDTH] = {
		{ ' ', ' ', ' ', 'r', ' ', ' ', ' ', ' ' },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'r' },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'r' },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'b' },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'b' },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'b' },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'b' },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'b' },
		{ ' ', ' ', ' ', ' ', ' ', ' ', 'b', 'b' },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'g' },
		{ ' ', ' ', ' ', ' ', 'r', ' ', ' ', 'b' },
		{ ' ', ' ', ' ', ' ', 'r', ' ', 'r', 'g' },
		{ ' ', ' ', ' ', ' ', 'b', 'r', 'b', 'g' },
		{ 'r', 'g', 't', 'p', 'b', 'p', 'b', 'g' },
		{ 'y', 'o', 'g', ' ', 'b', 'r', 'b', 'g' },
		{ 'y', 'y', 'y', 'r', 'b', 'b', 'g', 'g' }
	};

	// copy the test data I generated onto the board
	for (int row = 0; row<HEIGHT; row++)
		for (int col = 0; col<WIDTH; col++)
			board[row][col] = data[row][col];
};



//---------------------------------------------
	//mutators
void Well::addTetriminoToWell(Tetrimino* myTetrimino) {
	Location localLocation;
	int localGrid[SIZE][SIZE];

	localLocation.row = myTetrimino->getLocation().row;
	localLocation.col = myTetrimino->getLocation().col;
	myTetrimino->getGrid(localGrid);

	if (tetriminoFit(myTetrimino) == true) {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				if (localGrid[i][j] == 1) {
					board[localLocation.row + i][localLocation.col + j] = myTetrimino->getColor();
					
				}
			}
		 }
	 }
 }

 int Well::clearFullRows() {
	 int rowsCleared = 0;

	 for (int i = 0; i < HEIGHT; i++) {
		 if (rowIsFull(i) == true) {
			 moveRowsDown(i);
			 //for (int j = 0; j < WIDTH; j++) 
				 //board[i][j] = ' ';

			 rowsCleared++;
		 }
	 }


	 return rowsCleared;
 }

//---------------------------------------------
 //others
 void Well::boardDump() {
	 char tempBoard[HEIGHT][WIDTH];
	 getBoard(tempBoard);
	 std::cout << "___________" << endl;
	 for (int i = 0; i < HEIGHT; i++) {
		 std::cout << "| ";
		 for (int j = 0; j < WIDTH; j++) {
			 std::cout << tempBoard[i][j];
		 }
		 std::cout << " |" << i << endl;
	 }
	 std::cout << "[][][][][][]" << endl;
 }

 /*
int main() {
	// create a Well and a Tetrimino that I can use to test my Well class
	Well myWell;
	Tetrimino myTetrimino(0); // I generated a specific tetrimino to use for testing so I'd know whether or not it should fit at any given location

	// copy my test data onto the board and make sure it worked
	myWell.makeTestBoard();
	myWell.boardDump();

	std::cout << "Top reached? Should be true: " << myWell.topReached() << '\n'; // should be true since I stuck something in the top row

	myWell.clearFullRows(); // I should see the full rows in my test board disappear after calling this method
	myWell.boardDump();

	std::cout << "Top reached? Should be false: " << myWell.topReached() << '\n'; // should be false now that we've moved everything down two rows

	myTetrimino.setLocation(-4, -4);
	myWell.addTetriminoToWell(myTetrimino);
	myWell.boardDump(); // I should not see anything new in the well since the prior location of myTetrimino was out of bounds

	// Try a bunch of locations and see if the Tetrimino fits... you can modify these as you wish
	Location locations[12] = {
	{0, 0},
	{-1, -1},
	{-2, 0},
	{0, -2},
	{6, 0},
	{16, 3},
	{16, 4},
	{16, 5},
	{17, 3},
	{17, 4},
	{17, 5},
	{21, 1}
	};

	for (int loc = 0; loc < 12; loc++) {
		Location location = locations[loc];
		myTetrimino.setLocation(location);
		std::cout << location.row << ", " << location.col << ":  ";
		if (myWell.tetriminoFit(myTetrimino))
			std::cout << "it fits!\n";
		else
			std::cout << "doesn't fit!\n";
	}

	// add one that fits
	myTetrimino.setLocation({ 1,1 });
	myWell.addTetriminoToWell(myTetrimino);
	myWell.boardDump();

	return 1;
}
*/
