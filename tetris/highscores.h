#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Highscore {
	
private:
	int highscores[10];
	string names[10];
	static const string HIGHSCORE_FILE;

public:
	Highscore();

	void printHighscores();

	bool addName(string playerName, int playerHighscore);

	void uploadData();

	void getHighscores();

	void getNames();

	void returnHighscores(int hs[10]);
};
