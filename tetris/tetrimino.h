/*
@file		tetrimino.h
@author		Mark Stone
@version	1.0
The header file for tetrimino implementation
*/

#ifndef TETRIMINO_H
#define TETRIMINO_H

const int SIZE = 4;

struct Location {
	int row;
	int col;
};

class Tetrimino {
private:
	int grid[SIZE][SIZE]; //contains only zeros and ones 
	char color;
	Location location;
public:
	// constructor
	// Initialize grid, color, and location
	// The ‘type’ parameter will determine which piece we initialize grid to
	Tetrimino(int type = 7); // valid type values are 0-6

	//---------------------------------------------
	//accessors
	
	/*
	Returns the color of the Tetrimino

	@param n/a
	@return - the color of the current Tetrimino (‘r’=red, ‘y’=yellow, ‘t’=teal, ‘b’=blue, ‘o’=orange, ‘g’=green, ‘p’=purple)
	*/
	char getColor(); // returns the color of the tetrimino object

	/*
	Returns the location of the Tetrimino

	@param  - n/a
	@return - the location of the Tetrmino in (row, col) form.
	*/
	Location getLocation(); // return the location of the Tetrimino

	/*
	Returns the grid of the Tetrimino

	@param  - gridOut
	@return - the grid of the current Tetrimino
	*/
	void getGrid(int gridOut[][SIZE]);  // return the grid of the Tetrimino 

	//---------------------------------------------
	//mutators

	/*
	Sets the location of the Tetrimino

	@param newLocation - a set of coordinates for the new location in the form of a different struct
	@return - the modified location of the Tetrimino (grid),
			  set to the requested row/col.
	*/
	void setLocation(Location newLocation); // modify location.row and location.col

	/*
	Sets the location of the Tetrimino

	@param tetrimino - the Tetrimino to be rotated
	@return - the modified location of the Tetrimino (grid),
			  set to the requested row/col.
	*/
	void setLocation(int row, int col); // modify location.row and location.col

	/*
	Rotates the tetrimino to the left

	@param  row - the requested row of the location
			col - the requested column of the location
	@return - the modified version of the Tetrimino,
			  rotated to the left.
	*/
	void rotateLeft();

	/*
	Rotates the tetrimino to the right

	@param tetrimino - the Tetrimino to be rotated
	@return - the modified version of the Tetrimino,
			  rotated to the right.
	*/
	void rotateRight();

	/*
	Moves the tetrimino to the left

	@param tetrimino - the Tetrimino to be moved
	@return - the modified version of the Tetrimino,
			  moved to the left.
	*/
	void moveLeft();

	/*
	Moves the tetrimino to the right

	@param  - n/a
	@return - the modified version of the Tetrimino,
			  moved to the left.
	*/
	void moveRight();

	/*
	Moves the tetrimino down

	@param  - n/a
	@return - the modified version of the Tetrimino,
			  moved to the left.
	*/
	void moveDown();

	/*
	Moves the tetrimino up

	@param  - n/a
	@return - the modified version of the Tetrimino,
			  moved to the left.
	*/
	void moveUp();

	//---------------------------------------------
	//others
	void dataDump(); // print out the value of grid, color, and location  
};
#endif
