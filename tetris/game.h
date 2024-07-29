/*
@file		game.h
@author		Mark Stone
@version	1.0
The header file for game implementation
*/

#ifndef GAME_H
#define GAME_H

#include "well.h"
#include "tetrimino.h"
#include "highscores.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>


// Global Constants
const int LAYOUT_WINDOW_WIDTH  = 400;
const int LAYOUT_WINDOW_HEIGHT = 500;
const int LAYOUT_BOARD_TOP     = 10;
const int LAYOUT_BOARD_LEFT    = 200;
const int BLOCK_SIZE_PIXELS    = 20;
const int DEFAULT_GAME_SPEED   = 20;
const int DEFAULT_SOUND_VOLUME = 0;
const int DEFAULT_MUSIC_VOLUME = 0;
const string CONFIG_FILE = "../applicationdata/config.txt";

class Game {
private:

	Well* gameWell;
	Tetrimino* tetriminoInPlay;
	Tetrimino* tetriminoNext;
	Tetrimino* tetriminoHold;
	Tetrimino* tetriminoTemp;
	Tetrimino* ghostBlock;

	int gameSpeed;

	string playerName;

	int highscoresList[10];
	string namesList[10];

	int soundVolume;
	int musicVolume;

	enum GameState {
		TETRIS_SPLASH = 0,
		TETRIS_PLAY = 1,
		TETRIS_GAME_OVER = 2,
		TETRIS_HIGHSCORE = 3,
	};

	// SFML Objects
	sf::RenderWindow window;

	// Rectangles
	sf::RectangleShape well;
	sf::RectangleShape myBlock;
	sf::RectangleShape background;
	sf::RectangleShape playButton;
	sf::RectangleShape yesButton;
	sf::RectangleShape noButton;
	sf::RectangleShape nextButton;

	// Cursors
	sf::Cursor clickCursor;
	sf::Cursor normalCursor;

	// Colors
	sf::Color customColor;
	sf::Color textColor;
	sf::Color buttonColor;

	// Textures
	sf::Texture blankBlock;
	sf::Texture splashBackground;
	sf::Texture gameBackground;
	sf::Texture play;
	sf::Texture playInverse;
	sf::Texture again;
	sf::Texture againInverse;
	sf::Texture no;
	sf::Texture noInverse;
	sf::Texture next;
	sf::Texture nextInverse;
	sf::Texture gameOverBackground;

	// Music
	sf::Music music;

	// Font(s)
	sf::Font font;

	// Sounds
	sf::Sound right;
	sf::Sound left;
	sf::Sound levelUp;
	sf::Sound rotate;
	sf::Sound drop;

	// Sound Buffers
	sf::SoundBuffer bufferLeft;
	sf::SoundBuffer bufferRight;
	sf::SoundBuffer bufferLevelUp;
	sf::SoundBuffer bufferRotate;
	sf::SoundBuffer bufferDrop;

	int score;
	int tempScore;

	/*
	Converts a char representing a color into the SFML color

	@param char color - the color to be converted
	@return - the SFML version of the color
	*/
	sf::Color convertToSfmlColor(char color);

	/*
	Draws the well with all of the tetriminos inside of it

	@param 
		Well myWell		   - the well for the game
		int top            - the top offset (used to place the well 
							 in the correct spot.
		int left		   - the left offset (used to place the well
							 in the correct spot.
		int blockPixelSize - the size (in pixels) of the Tetrimino blocks
	@return - n/a
	*/
	void drawWell(Well* myWell, int top, int left, int blockPixelSize);

	/*
	Draws the well with all of the tetriminos inside of it

	@param
		Tetrimino myTetrimino - the active Tetrimino in the game
		int top               - the top offset (used to place the well
							    in the correct spot.
		int left	   	      - the left offset (used to place the well
							    in the correct spot.
		int blockPixelSize    - the size (in pixels) of the Tetrimino blocks
	@return - n/a
	*/
	void drawTetrimino(Tetrimino* myTetrimino, int top, int left, int blockPixelSize);

public:
	// constructor
	// Initialize the game
	Game();

	/*
	Contains all of the code to run the game

	@param n/a
	@return - n/a
	*/
	void playGame();

	/*
	Contains all of the code to display the splash screen.

	@param n/a
	@return - n/a
	*/
	void processSplash();

	/*
	Contains all of the code to process the game and display it.

	@param n/a
	@return - n/a
	*/
	void processGame();

	/*
	Contains all of the code to display the game over screen and gives
	the user the option to play again or quit.

	@param n/a
	@return - n/a
	*/
	bool processGameOver();

	void processHighscore();

	/*
	Gets the level the player is currently on. Used to speed the game up,
	as well as calculating the score.

	@param int rowsCleared - the total number of rows the player has cleared
	@return - currentLvl - the player's current level
	*/
	int level(int rowsCleared);

	/*
	Draws the score of the player at [top], [left]

	@param int score - the score of the player to be displayed
		   int top   - the x coordinate to place the score on the screen
		   int left  - the y coordinate to place the score on the screen
	@return - the score in the window placed where it was requested
	*/
	void drawScore(int score, int top, int left);
	
	/*
	Draws the level of the player at [top], [left]

	@param int rowsCleared - the score of the player to be displayed
		   int top         - the x coordinate to place the score on the screen
		   int left        - the y coordinate to place the score on the screen
	@return - the level in the window placed where it was requested
	*/
	void drawLevel(int rowsCleared, int top, int left);

	void getPlayerName();

};
#endif
