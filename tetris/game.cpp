/*
@file		game.cpp
@author		Mark Stone
@version	1.1
The header file for game implementation
*/

#include <iostream>
#include "game.h"
#include <sstream>

using namespace std;

Game::Game() {
	tetriminoNext = NULL;
	tetriminoInPlay = NULL;
	tetriminoHold = NULL;
	ghostBlock = NULL;
	gameWell = NULL;

	score = 0;
	gameSpeed = DEFAULT_GAME_SPEED;
	soundVolume = DEFAULT_SOUND_VOLUME;
	musicVolume = DEFAULT_MUSIC_VOLUME;

	sf::Vector2i position = sf::Mouse::getPosition(window);

	// load and set the font
	font.loadFromFile("resources/Nunito/Nunito-Bold.ttf");

	// load cursors from system
	clickCursor.loadFromSystem(sf::Cursor::Hand);
	normalCursor.loadFromSystem(sf::Cursor::Arrow);
	
	// load splash background
	splashBackground.loadFromFile("resources/tetris_background_splash.png");
	gameBackground.loadFromFile("resources/tetris_background_game.png");
	gameOverBackground.loadFromFile("resources/tetris_background_game_over.png");

	background.setSize(sf::Vector2f(LAYOUT_WINDOW_WIDTH, LAYOUT_WINDOW_HEIGHT));
	background.setPosition(0, 0);

	// load and set move left sound
	bufferLeft.loadFromFile("resources/move_right.ogg");
	left.setBuffer(bufferLeft);
	left.setVolume(soundVolume);

	// load and set move right sound
	bufferRight.loadFromFile("resources/move_left.ogg");
	right.setBuffer(bufferRight);
	right.setVolume(soundVolume);

	// load and set level up sound
	bufferLevelUp.loadFromFile("resources/level_up.ogg");
	levelUp.setBuffer(bufferLevelUp);
	levelUp.setVolume(soundVolume);

	// load and set rotate sound
	bufferRotate.loadFromFile("resources/rotate.ogg");
	rotate.setBuffer(bufferRotate);
	rotate.setVolume(soundVolume);

	// load and set drop sound
	bufferDrop.loadFromFile("resources/drop.ogg");
	drop.setBuffer(bufferDrop);
	drop.setVolume(soundVolume);

	// load the textures
	blankBlock.loadFromFile("resources/tetrimino_block.png");
	play.loadFromFile("resources/play_button.png");
	playInverse.loadFromFile("resources/play_button_inverse.png");
	again.loadFromFile("resources/yes_button.png");
	againInverse.loadFromFile("resources/yes_button_inverse.png");
	no.loadFromFile("resources/no_button.png");
	noInverse.loadFromFile("resources/no_button_inverse.png");
	next.loadFromFile("resources/next_button.png");
	nextInverse.loadFromFile("resources/next_button_inverse.png");

	// load and set/play the game music
	// song: Tetris Theme Song
	if (!music.openFromFile("resources/Tetris.ogg"))
		cout << "Error" << endl;
	music.setVolume(musicVolume);
	music.setLoop(true);
	music.play();

	playButton.setSize(sf::Vector2f(133, 50));
	playButton.setPosition(257, 437);

	yesButton.setSize(sf::Vector2f(133, 50));
	yesButton.setPosition(10, 437);

	noButton.setSize(sf::Vector2f(133, 50));
	noButton.setPosition(257, 437);

	nextButton.setSize(sf::Vector2f(133, 50));
	nextButton.setPosition(257, 437);

	window.create(
		sf::VideoMode(LAYOUT_WINDOW_WIDTH, LAYOUT_WINDOW_HEIGHT),
		"Tetris 2019",
		sf::Style::Titlebar | sf::Style::Close);
		window.setFramerateLimit(30);
}

sf::Color Game::convertToSfmlColor(char color) {
	if (color == 'r') {
		sf::Color customColor(255, 50, 0);
		return customColor;
	}

	else if (color == 'y') {
		sf::Color customColor(200, 255, 20);
		return customColor;
	}

	else if (color == 't') {
		sf::Color customColor(18, 223, 255);
		return customColor;
	}

	else if (color == 'b') {
		sf::Color customColor(40, 46, 235);
		return customColor;
	}

	else if (color == 'o') {
		sf::Color customColor(255, 148, 18);
		return customColor;
	}

	else if (color == 'g') {
		sf::Color customColor(41, 255, 41);
		return customColor;
	}

	else if (color == 'p') {
		sf::Color customColor(164, 18, 255);
		return customColor;
	}
	return sf::Color::Transparent;
}

void Game::drawWell(Well* myWell, int top, int left, int blockPixelSize) {
	char localBoard[HEIGHT][WIDTH];
	myWell->getBoard(localBoard);
	
	well.setSize(sf::Vector2f((WIDTH * blockPixelSize), (HEIGHT * blockPixelSize)));
	well.setOutlineThickness(1);
	well.setOutlineColor(sf::Color::Magenta);
	well.setFillColor(sf::Color::White);
	well.setPosition(left, top);
	window.draw(well);

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			
			if (localBoard[i][j] != ' ') {
				myBlock.setFillColor(convertToSfmlColor(localBoard[i][j]));
				myBlock.setTexture(&blankBlock);
				myBlock.setPosition((left + (j * blockPixelSize)), (top + (i * blockPixelSize)));
				
				window.draw(myBlock);
			}
		}
	}
}

void Game::drawTetrimino(Tetrimino* myTetrimino, int top, int left, int blockPixelSize) {
	Location localLocation;
	localLocation.row = myTetrimino->getLocation().row;
	localLocation.col = myTetrimino->getLocation().col;

	int localGrid[SIZE][SIZE];
	myTetrimino->getGrid(localGrid);

	myBlock.setSize(sf::Vector2f(blockPixelSize, blockPixelSize));
	
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (localGrid[i][j] == 1 && localLocation.row + i >= 0) {
				myBlock.setFillColor(convertToSfmlColor(myTetrimino->getColor()));
				myBlock.setTexture(&blankBlock);
				myBlock.setPosition(((j * blockPixelSize) + (left + (localLocation.col * blockPixelSize))),
					((i * blockPixelSize) + (top + (localLocation.row * blockPixelSize))));
				window.draw(myBlock);
			}
		}
	}
}

int Game::level(int rowsCleared) {
	int currentLvl = 1;
	
	if (rowsCleared >= 5 && rowsCleared < 10) {
		currentLvl = 2;
		gameSpeed = 19;
		return currentLvl;
	}
	else if (rowsCleared >= 10 && rowsCleared < 15) {
		currentLvl = 3;
		gameSpeed = 18;
		return currentLvl;
	}
	else if (rowsCleared >= 15 && rowsCleared < 25) {
		currentLvl = 4;
		gameSpeed = 17;
		return currentLvl;
	}
	else if (rowsCleared >= 25 && rowsCleared < 40) {
		currentLvl = 5;
		gameSpeed = 16;
		return currentLvl;
	}
	else if (rowsCleared >= 40 && rowsCleared < 60) {
		currentLvl = 6;
		gameSpeed = 15;
		return currentLvl;
	}
	else if (rowsCleared >= 60 && rowsCleared < 70) {
		currentLvl = 7;
		gameSpeed = 14;
		return currentLvl;
	}
	else if (rowsCleared >= 70 && rowsCleared < 90) {
		currentLvl = 8;
		gameSpeed = 13;
		return currentLvl;
	}
	else if (rowsCleared >= 90 && rowsCleared < 120) {
		currentLvl = 9;
		gameSpeed = 12;
		return currentLvl;
	}
	else if (rowsCleared >= 120 && rowsCleared < 150) {
		currentLvl = 10;
		gameSpeed = 11;
		return currentLvl;
	}
	else if (rowsCleared >= 150 && rowsCleared < 180) {
		currentLvl = 11;
		gameSpeed = 10;
		return currentLvl;
	}
	else if (rowsCleared >= 180 && rowsCleared < 200) {
		currentLvl = 12;
		gameSpeed = 9;
		return currentLvl;
	}
	else if (rowsCleared >= 200 && rowsCleared < 250) {
		currentLvl = 13;
		gameSpeed = 8;
		return currentLvl;
	}
	else if (rowsCleared >= 250 && rowsCleared < 300) {
		currentLvl = 14;
		gameSpeed = 7;
		return currentLvl;
	} 
	else if (rowsCleared >= 300 && rowsCleared < 400) {
		currentLvl = 15;
		gameSpeed = 6;
		return currentLvl;
	}
	else {
		return currentLvl;
	}
}

void Game::playGame() {
	GameState gameState = TETRIS_SPLASH;
	
	while (window.isOpen()) {
		if (gameState == TETRIS_SPLASH) {
			processSplash();
			gameState = TETRIS_PLAY;
		}
		else if (gameState == TETRIS_PLAY) {
			processGame();
			gameState = TETRIS_HIGHSCORE;
		}
		else if (gameState == TETRIS_HIGHSCORE) {
			processHighscore();
			gameState = TETRIS_GAME_OVER;
		}
		else if (gameState == TETRIS_GAME_OVER) {
			sf::Time sleepTime = sf::seconds(0.1f);
			sleep(sleepTime); // Sleep briefly to prevent any overlap in input
			if (processGameOver() == true) {
				gameState = TETRIS_PLAY;
			} else {
				window.close();
			}
		}
	}
}

void Game::processSplash() {
	bool exit = false;
	background.setTexture(&splashBackground);

	while (window.isOpen()) {
		sf::Event event;

		window.draw(background);

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		sf::Vector2i position = sf::Mouse::getPosition(window);
		if (position.x >= 257 && 
			position.x <= 388 && 
			position.y >= 437 && 
			position.y <= 485) {
				window.setMouseCursor(clickCursor);
				playButton.setTexture(&playInverse);
				window.draw(playButton);
		}
		else {
			window.setMouseCursor(normalCursor);
			playButton.setTexture(&play);
			window.draw(playButton);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && 
			position.x >= 257 && 
			position.x <= 388 && 
			position.y >= 437 && 
			position.y <= 485) {
			window.setMouseCursor(normalCursor);
			exit = true;
		}

		window.display();
		if (exit == true) {
			break;	
		}
	}
}

void Game::processGame() {
	gameWell = new Well;
	tetriminoNext = new Tetrimino;
	tetriminoInPlay = new Tetrimino;
	tetriminoInPlay->setLocation(-2, 2);

	int currentLevel = 1;
	int counter = 0;
	int totalRows = 0;
	int rowsInOne = 0;
	bool firstTime = true;
	bool hasSwitched = false;

	music.setVolume(musicVolume);

	background.setTexture(&gameBackground);

	while (window.isOpen() && gameWell->topReached() == false) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
				tetriminoInPlay->moveLeft();
				right.play();

				if (gameWell->tetriminoFit(tetriminoInPlay) == false)
					tetriminoInPlay->moveRight();
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
				tetriminoInPlay->moveRight();
				left.play();

				if (gameWell->tetriminoFit(tetriminoInPlay) == false)
					tetriminoInPlay->moveLeft();
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
				tetriminoInPlay->rotateRight();
				rotate.play();
				if (gameWell->tetriminoFit(tetriminoInPlay) == false)
					tetriminoInPlay->rotateLeft();
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
				tetriminoInPlay->moveDown();
				score += 10;
				if (gameWell->tetriminoFit(tetriminoInPlay) == false) {
					tetriminoInPlay->moveUp();
					score -= 10;
				}
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
				while (gameWell->tetriminoFit(tetriminoInPlay) == true) {
					tetriminoInPlay->moveDown();
					score += 10;
				}
				tetriminoInPlay->moveUp();
				drop.play();
				score -= 10;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::RShift) {
				if (firstTime == true) {
					tetriminoHold = tetriminoInPlay;
					tetriminoHold->setLocation(0, 0);
					tetriminoInPlay = tetriminoNext;
					tetriminoInPlay->setLocation(-2, 2);
					tetriminoNext = new Tetrimino;
					firstTime = false;
				}
				else if (firstTime == false && hasSwitched == false) {
					tetriminoTemp = tetriminoHold;
					tetriminoHold = tetriminoInPlay;
					tetriminoHold->setLocation(0, 0);
					tetriminoInPlay = tetriminoTemp;
					tetriminoInPlay->setLocation(-2, 2);
					hasSwitched = true;
				}
			}
		}

		counter++;
		if (counter == gameSpeed) {
			tetriminoInPlay->moveDown();
			counter = 0;
			if (gameWell->tetriminoFit(tetriminoInPlay) == false) {
				tetriminoInPlay->moveUp();
				gameWell->addTetriminoToWell(tetriminoInPlay);
				delete tetriminoInPlay;
				
				rowsInOne += gameWell->clearFullRows();
				totalRows += rowsInOne;

				if (rowsInOne == 4) {
					score += level(totalRows) * 4 * 10 * rowsInOne;
					rowsInOne = 0;
				}
				else {
					score += level(totalRows) * 10 * rowsInOne;
					rowsInOne = 0;
				}

				if (gameWell->topReached() == true) {
					tempScore = score;
					score = 0;
					tetriminoHold = NULL;
					break;
				}
				else {
					tetriminoInPlay = tetriminoNext;
					tetriminoInPlay->setLocation(-2, 2);
					tetriminoNext = new Tetrimino;
					hasSwitched = false;
				}
			}
		}

		if (level(totalRows) > currentLevel) {
			currentLevel++;
			levelUp.play();
		}

		window.clear();
		window.draw(background);
		
		drawTetrimino(tetriminoNext, 35, 87, 20);
		if (tetriminoHold != NULL)
			drawTetrimino(tetriminoHold, 167, 87, 20);
		
		drawWell(gameWell, LAYOUT_BOARD_TOP, LAYOUT_BOARD_LEFT, BLOCK_SIZE_PIXELS);
		drawTetrimino(tetriminoInPlay, LAYOUT_BOARD_TOP, LAYOUT_BOARD_LEFT, BLOCK_SIZE_PIXELS);
		drawLevel(totalRows, 26, 12);
		drawScore(score, 90, 451);
		
		window.display();
	}
}

bool Game::processGameOver() {
	background.setTexture(&gameOverBackground);
	music.setVolume(0);

	while (window.isOpen()) {
		window.clear();
		sf::Event event;
		sf::Text lose;

		window.draw(background);

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				return false;
				window.close();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace) {
				return false;
				window.close();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
				return true;
				window.close();
			}
		}

		sf::Vector2i position = sf::Mouse::getPosition(window);
		if (position.x >= 257 &&
			position.x <= 388 &&
			position.y >= 437 &&
			position.y <= 485) {
			window.setMouseCursor(clickCursor);
			noButton.setTexture(&noInverse);
		}
		else if (position.x >= 10 &&
			position.x <= 143 &&
			position.y >= 437 &&
			position.y <= 485) {
			window.setMouseCursor(clickCursor);
			yesButton.setTexture(&againInverse);
		} 
		else {
			window.setMouseCursor(normalCursor);
			noButton.setTexture(&no);
			yesButton.setTexture(&again);
		}
		window.draw(yesButton);
		window.draw(noButton);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && 
			position.x >= 257 &&
			position.x <= 388 &&
			position.y >= 437 &&
			position.y <= 485) {
			window.setMouseCursor(normalCursor);
			return false;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && 
			position.x >= 10 &&
			position.x <= 143 &&
			position.y >= 437 &&
			position.y <= 485) {
			window.setMouseCursor(normalCursor);
			return true;
		}

		window.display();
	}
	return false;
}

void Game::drawLevel(int rowsCleared, int top, int left) {
	stringstream lvl;
	lvl << level(rowsCleared);

	sf::Text printLevel;
	printLevel.setFont(font);
	printLevel.setFillColor(sf::Color::Black);
	printLevel.setCharacterSize(50);
	printLevel.setString(lvl.str());
	
	if (level(rowsCleared) >= 10) {
		printLevel.setPosition(top - 16, left);
	}
	else {
		printLevel.setPosition(top, left);
	}

	window.draw(printLevel);

}

void Game::processHighscore() {
	Highscore hs;
	string name;

	sf::Event event;
	stringstream pName;
	sf::Text highscoreList;

	getPlayerName();

	hs.getHighscores();
	hs.getNames();
	hs.printHighscores();
	if (hs.addName(playerName, tempScore) == true) {
		cout << "Success." << endl;
	}
	else {
		cout << "Failed." << endl;
	}
	hs.printHighscores();
	hs.uploadData();

	cout << "\nPlayer Name: " << playerName << "\nScore: " << tempScore << endl;
	highscoreList.setFont(font);
	highscoreList.setPosition(50, 50);
	highscoreList.setCharacterSize(20);
	highscoreList.setFillColor(sf::Color::White);
	while (window.isOpen()) {
		window.clear();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Vector2i position = sf::Mouse::getPosition(window);
		if (position.x >= 257 &&
			position.x <= 388 &&
			position.y >= 437 &&
			position.y <= 485) {
				window.setMouseCursor(clickCursor);
				nextButton.setTexture(&nextInverse);
		} else {
			window.setMouseCursor(normalCursor);
			nextButton.setTexture(&next);
		}

		window.draw(nextButton);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
			position.x >= 257 &&
			position.x <= 388 &&
			position.y >= 437 &&
			position.y <= 485) {
			window.setMouseCursor(normalCursor);
			break;
		}

		window.draw(highscoreList);
		window.display();
	}
}


void Game::drawScore(int score, int top, int left) {
	stringstream sc;
	sc << score;

	sf::Text printScore;
	printScore.setFont(font);
	printScore.setFillColor(sf::Color::Black);
	printScore.setCharacterSize(20);
	printScore.setPosition(top, left);
	printScore.setString(sc.str());
	window.draw(printScore);
}

void Game::getPlayerName() {
	string name;
	ifstream file(CONFIG_FILE);
	int numLines = 0;
	if (file.is_open()) {
		while (getline(file, name)) {
			if (numLines % 2) {
				playerName = "Anonymous";
			}
			else {
				playerName = name;
			
			}
			numLines++;
		}
	}
}

int main() {
	Game game;
	game.playGame();
	return 0;
}