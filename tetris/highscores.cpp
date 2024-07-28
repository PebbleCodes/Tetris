#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "highscores.h"

using namespace std;

const string Highscore::HIGHSCORE_FILE = "../applicationdata/highscores.txt";

Highscore::Highscore() {
	for (int i = 0; i < 10; i++)
		highscores[i] = 0;
}

void Highscore::printHighscores() {
	cout << "\nHighscores:\n\n";
	for (int i = 0; i < 10; i++)
		if (i < 9)
			cout << " " << i + 1 << ". " << names[i] << " " << highscores[i] << endl;
		else
			cout << i + 1 << ". " << names[i] << " " << highscores[i] << endl;
}

void Highscore::getHighscores() {
	string number;
	int result;
	ifstream file(HIGHSCORE_FILE);
	int i = 0;
	if (file.is_open()) {
		while (getline(file, number)) {
			istringstream convert(number);
			if (!(convert >> result)) {
				result = 0;
			}
			else {
				highscores[i] = result;
				i++;
			}
		}
	}
}

void Highscore::getNames() {
	string name;
	ifstream file(HIGHSCORE_FILE);
	int i = 0;
	int numLines = 0;
	if (file.is_open()) {
		while (getline(file, name)) {
			if (numLines % 2) {
				// filter out the numbers, since I only want the names (which are all on odd lines)
			}
			else {
				names[i] = name;
				i++;
			}
			numLines++;
		}
	}
}

bool Highscore::addName(string playerName, int playerScore) {
	cout << playerName << endl;
	cout << playerScore << endl;
	for (int i = 0; i < 10; i++) {
		if (playerScore > highscores[i]) {
			for (int j = 8; j >= i; j--) {
				highscores[j + 1] = highscores[j];
				names[j + 1] = names[j];
			}
			names[i] = playerName;
			highscores[i] = playerScore;
			

			return true;
		}
	}
	return false;
}

void Highscore::uploadData() {
	ofstream file;
	file.open(HIGHSCORE_FILE);
	for (int i = 0; i < 10; i++) {
		file << names[i] << endl;
		file << highscores[i] << endl;
	}
	file.close();
}

void Highscore::returnHighscores(int hs[10]) {
	for (int i = 0; i < 10; i++) {
		hs[i] = highscores[i];
	}
}

/*
int main() {
	Highscore hs;
	string namess;
	int highscoress;

	hs.printHighscores();
	hs.getHighscores();
	hs.getNames();
	cout << endl;
	hs.printHighscores();

	cout << "Name: ";
	cin >> namess;
	cout << "Highscore: ";
	cin >> highscoress;
	if (hs.addName(namess, highscoress) == true) {
		cout << "Name Added" << endl;
	}
	else {
		cout << "Name not Added" << endl;
	}
	hs.printHighscores();
	hs.uploadData();
	
	
	ofstream myFile;
	int highscore;
	string name;
	cout << "Please enter your name: ";
	cin >> name;
	cout << "Please enter your highscore: ";
	cin >> highscore;

	myFile.open("highscores.txt");
	myFile << name << "\n" << highscore;
	myFile.close();

	string line;
	ifstream file("highscores.txt");
	if (file.is_open()) {
		while (getline(file, line)) {
			cout << line << "\n";
		}
		file.close();
	}
	cin >> highscore;
	return 0;
}*/