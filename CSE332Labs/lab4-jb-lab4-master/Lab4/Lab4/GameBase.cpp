
#include "stdafx.h"
#include "TicTacToeGame.h"
#include"commonFunctions.h"
#include"Gomoku.h"
#include<string>
#include<iostream>
#include<sstream>
#include<iomanip>


int GameBase::prompt(unsigned int &x, unsigned int &y) {
	cout << " Please enter a valid coordinat as a comma-separated pair of integers: #,#" << endl;
	cout << "Or type 'quit' to end the game" << endl;
	while (inProgress) { // prompt user until noErrors is returned
		string input;
		cin >> input;
		istringstream is(input);
		string res;
		is >> res; // wrap input then check if it equals quit
		if (res == "quit") {
			return userQuit;
		}

		// turn comma into whitespace
		for (unsigned int i = 0; i < input.size(); ++i) {
			if (input[i] == ',') {
				input[i] = ' ';
			}

		}

		istringstream iss(input); // wrap input
		int tempX;
		int tempY;
		while (iss) {
			iss >> tempX; iss >> tempY;
		}
		if (tempX < width && tempX > 0 && tempY < height && tempY > 0) { // make sure coordinates are playable
			x = tempX;
			y = tempY;
			return noErrors;
		}
		else {

			cout << "incorrect format or board position" << endl;
			cout << "use form: #,#" << endl;
		}
	}
}
//gameplay
int GameBase::play() {
	while (inProgress) { // wait for different return value
		if (turn() == userQuit) {
			print();
			cout << "User Quit" << endl;
			return userQuit;
		}
		if (done() == true) {
			print();
			cout << player << " won the game " << endl;
			return noErrors;
		}
		if (draw() == true) {
			print();
		
			return endedInDraw;
		}
	}
}


GameBase* GameBase::getGame(int argc, char *argv[])
{
	// name of program + tictactoe
	string programName = argv[inputIndex];
	if (argc == expectedNumberOfArguments) {
		if (programName == "TicTacToe") {
			return new TicTacToeGame();
		}
		else if (programName == "Gomoku") {
			return new GomokuGame();
		}
	}
	return 0;
}
