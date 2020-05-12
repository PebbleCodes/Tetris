/*
@file		well.h
@author		Mark Stone
@version	1.0
The header file for well implementation
*/

#ifndef WELL_H
#define WELL_H

#include "tetrimino.h"

const int HEIGHT = 24;
const int WIDTH  = 8;

class Well {
private:
	char board[HEIGHT][WIDTH];

	/*
	Returns whether or not the specified row is full

	@param int row - the row you are testing to see if its full
	@return - True : The row is full
			  False: The row is not full
	*/
	bool rowIsFull(int row);

	/*
	Moves all of the rows down by one, used for when you clear a full row

	@param int firstRowToMove - the row you are moving down first
	@return - n/a
	*/
	void moveRowsDown(int firstRowToMove);
	
public:
	// constructor
	// Initialize the well
	Well(int height = 24, int width = 8);

	//---------------------------------------------
	//accessors

	/*
	Returns whether or not the Tetrimino fits 

	@param myTetrimino - The Tetrimino you want to test
	@return - true : Tetrimino fits
			  false: Tetrimino does not fit
	*/
	bool tetriminoFit(Tetrimino* myTetrimino);

	/*
	Returns whether or not the top has been reached

	@param n/a
	@return - true : if the top has been reached
			  false: if the top has not been reached
	*/
	bool topReached();

	/*
	Accesses the board (private)

	@param n/a
	@return - n/a
	*/
	void getBoard(char myGrid[][8]);

	/*
	Tests all of the functions

	@param n/a
	@return - a complete test of every function in well.cpp
	*/
	void makeTestBoard();
	
	//---------------------------------------------
	//mutators

	/*
	Adds a Tetrimino into the well

	@param myTetrimino - the Tetrimino piece you want to add into the board
	@return - n/a
	*/
	void addTetriminoToWell(Tetrimino* myTetrimino);

	/*
	Clears the rows that are full and increments the amount of rowsCleared variable

	@param n/a
	@return - rowsCleared: the number of rows that have been cleared
	*/
	int clearFullRows();

	//---------------------------------------------
	//others

	/*
	Prints out the board 

	@param n/a
	@return - n/a
	*/
	void boardDump();
	
};
#endif
