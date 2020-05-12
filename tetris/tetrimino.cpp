/*
@file		tetrimino.cpp
@author		Mark Stone
@version	1.0
The header file for tetrimino implementation
*/

#include <iostream>
#include <ctime>
#include "tetrimino.h"

using namespace std;


// valid type values are 0-6
Tetrimino::Tetrimino(int type) {
	

	//‘r’=red, ‘y’=yellow, ‘t’=teal, ‘b’=blue, ‘o’=orange, ‘g’=green, ‘p’=purple
	char tColor[8] = { 'r', 'y', 't', 'b', 'o', 'g', 'p'};

	Tetrimino::location = { 0,0 };

	// Tetrimino Initialization
	int iTetrimino[][SIZE] = {
		{0, 0, 0, 0},
		{1, 1, 1, 1},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
	};

	int jTetrimino[][SIZE] = {
		{0, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 1, 1},
		{0, 0, 0, 0},
	};

	int lTetrimino[][SIZE] = {
		{0, 0, 0, 0},
		{0, 0, 0, 1},
		{0, 1, 1, 1},
		{0, 0, 0, 0},
	};

	int oTetrimino[][SIZE] = {
		{0, 0, 0, 0},
		{0, 1, 1, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0},
	};

	int sTetrimino[][SIZE] = {
		{0, 0, 0, 0},
		{0, 0, 1, 1},
		{0, 1, 1, 0},
		{0, 0, 0, 0},
	};

	int tTetrimino[][SIZE] = {
		{0, 0, 0, 0},
		{0, 1, 1, 1},
		{0, 0, 1, 0},
		{0, 0, 0, 0},
	};

	int zTetrimino[][SIZE] = {
		{0, 0, 0, 0},
		{0, 1, 1, 0},
		{0, 0, 1, 1},
		{0, 0, 0, 0},
	};

	static bool firstTime = true;

	if (firstTime) {
		srand(static_cast<unsigned int>(time(NULL)));
		firstTime = false;
	}

	// Generate a random number if type is invalid
	if (type < 0 || type > 6) {
		type = rand() % 7;
	}

	switch (type) {
	case 0:
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				Tetrimino::grid[i][j] = iTetrimino[i][j];
				Tetrimino::color = tColor[0];
			}
		}
		break;
	case 1:
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				grid[i][j] = jTetrimino[i][j];
				Tetrimino::color = tColor[1];
			}
		}
		break;
	case 2:
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				grid[i][j] = lTetrimino[i][j];
				Tetrimino::color = tColor[2];
			}
		}
		break;
	case 3:
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				grid[i][j] = oTetrimino[i][j];
				Tetrimino::color = tColor[3];
			}
		}
		break;
	case 4:
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				grid[i][j] = sTetrimino[i][j];
				Tetrimino::color = tColor[4];
			}
		}
		break;
	case 5:
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				grid[i][j] = tTetrimino[i][j];
				Tetrimino::color = tColor[5];
			}
		}
		break;
	case 6:
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				grid[i][j] = zTetrimino[i][j];
				Tetrimino::color = tColor[6];
			}
		}
		break;
	}
}

	//---------------------------------------------
	//accessors
// returns the color of the tetrimino object
char Tetrimino::getColor() {
	return color;
}

// return the location of the Tetrimino
Location Tetrimino::getLocation() {
	return location;
}

// return the grid of the Tetrimino 
void Tetrimino::getGrid(int gridOut[][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			gridOut[i][j] = grid[i][j];
		}
	}
}

//---------------------------------------------
//mutators
// modify location.row and location.col
void Tetrimino::setLocation(Location newLocation) {
	Tetrimino::location = newLocation;
}

// modify location.row and location.col
void Tetrimino::setLocation(int row, int col) {
	location.row = row;
	location.col = col;
}

void Tetrimino::rotateLeft() {
	int copyArray[SIZE][SIZE];
	getGrid(copyArray);
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			copyArray[i][j] = grid[j][SIZE - i - 1];
		}
	}

	for (int x = 0; x < SIZE; x++) {
		for (int y = 0; y < SIZE; y++) {
			grid[x][y] = copyArray[x][y];
		}
	}
}

void Tetrimino::rotateRight() {
	int copyArray[SIZE][SIZE];
	getGrid(copyArray);
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			copyArray[i][j] = grid[SIZE - j - 1][i];
		}
	}

	for (int x = 0; x < SIZE; x++) {
		for (int y = 0; y < SIZE; y++) {
			grid[x][y] = copyArray[x][y];
		}
	}
}

void Tetrimino::moveLeft() {
	location.col = location.col - 1;
}

void Tetrimino::moveRight() {
	location.col = location.col + 1;
}

void Tetrimino::moveDown() {
	location.row = location.row + 1;
}

void Tetrimino::moveUp() {
	location.row = location.row - 1;
}

//---------------------------------------------
//others
void Tetrimino::dataDump() { // print out the value of grid, color, and location
	int tempGrid[SIZE][SIZE];

	cout << "Grid: " << endl; 
	getGrid(grid);
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			cout << tempGrid[i][j];
		}
		cout << endl;
	}
	cout << endl;
	
	cout << endl;
	cout << "Color: " << getColor() << endl;
	cout << "Location: " <<  getLocation().row << ", " << getLocation().col<< endl;
}
/*
int main() {
	Tetrimino test;
	test.dataDump();
	test.setLocation(2, 3);
	test.dataDump();
	test.moveDown();
	test.dataDump();
	test.moveLeft();
	test.dataDump();
	test.moveRight();
	test.moveRight();
	test.moveRight();
	test.moveRight();
	test.dataDump();

	Tetrimino test2(2);
	test2.setLocation(1, 1);
	test2.dataDump();

	return 0;
}
*/