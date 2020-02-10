#include "stdafx.h"
#include "TicTacToeGame.h"
#include"commonFunctions.h"
#include<string>
#include<iostream>
#include<sstream>
TicTacToeGame::TicTacToeGame(){
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			gameBoard[i][j] = " ";
		}
	}
	numberOfMoves = 0;

	xCoordinate = 10; // set coordinates so they're off the board
	yCoordinate = 10;
	//set axis labels
	gameBoard[0][0] = "4";
	gameBoard[1][0] = "3";
	gameBoard[2][0] = "2";
	gameBoard[3][0] = "1";
	gameBoard[4][0] = "0";
	gameBoard[5][1] = "0";
	gameBoard[5][2] = "1";
	gameBoard[5][3] = "2";
	gameBoard[5][4] = "3";
	gameBoard[5][5] = "4";
	player = "O"; // O goes first
}

std::ostream& operator << (std::ostream& out, const TicTacToeGame& TTT) {
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			out << TTT.gameBoard[i][j] << " ";
		}
		out << endl;
	}
	return out;
}

bool TicTacToeGame::done() {
	for (int i = 1; i < 4; ++i) { //horizontal win
		if (gameBoard[i][2] == gameBoard[i][3] && gameBoard[i][3] == gameBoard[i][4] && gameBoard[i][2] != " ") {
			return true;
		}
	}

	for (int i = 2; i < 5; ++i) { //vertical win
		if (gameBoard[1][i] == gameBoard[2][i] && gameBoard[2][i] == gameBoard[3][i] && gameBoard[2][i] != " ") {
			return true;
		}
	}
	
	if (gameBoard[2][3] == " ") { //no diagonal win if middle is blank
		return false;
	}
	//diagonal win chacks
	else if (gameBoard[1][2] == gameBoard[2][3] && gameBoard[2][3] == gameBoard[3][4]) {
		return true;
	}
	else if (gameBoard[1][4] == gameBoard[2][3] && gameBoard[2][3] == gameBoard[3][2]) {
		return true;
	}
	return false;
}

bool TicTacToeGame::draw() {
	// has to be 9 moves for a draw (since done() is called before draw() in play(), if done() is true, that value will be returned before draw is even called) so no need to check it here
	if (numberOfMoves == 9) { 
		return true;
	}

	return false;
}

int TicTacToeGame::prompt(unsigned int &x, unsigned int &y) {
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
	if (tempX < 4 && tempX > 0 && tempY < 4 && tempY > 0) { // make sure coordinates are playable
		x = tempX;
		y = tempY;
		return noErrors;
	}
	else{

		cout << "incorrect format or board position (only middle 3x3 is playable)" << endl;
		cout<< "use form: #,#" << endl;
	}
}
}

int TicTacToeGame::turn() {
	if (player == "X") { //switch player
		player = "O";
	}
	else {
		player = "X";
	}
	cout << "Player " << player << "'s turn" << endl << endl;
	unsigned int tempX;
	unsigned int tempY;
	
	while (inProgress) { // loop until noErrors
		if (prompt(xCoordinate, yCoordinate) == userQuit) {
			return userQuit;
		}
		//adjust coordinates for visual display/gameboard values
		if (xCoordinate == 1) { 
			tempX = 3;
		}
		else if (xCoordinate == 3) {
			tempX = 1;
		}
		else {
			tempX = 2;
		}
		tempY = yCoordinate + 1;
		if (gameBoard[tempX][tempY] == " ") {
			gameBoard[tempX][tempY] = player;
			cout << *this << endl; // print gameboard
			++numberOfMoves;
			break;
		}
		else {
			cout << "coordinates already played" << endl;
		}
	}
		//formatting for print statement about players moves
		stringstream ss;
		ss << tempX << "," << tempY << "; ";
		string move;
		ss >> move;
		if (player == "X") {
			xMoves += move;
			cout << "Player " << player << ": " << xMoves << endl << endl;
			
		}
		else {
			oMoves += move;
			cout << "Player " << player << ": " << oMoves << endl << endl;
			
		}
	
	return noErrors;
}
//gameplay
int TicTacToeGame::play() {
	while (inProgress) { // wait for different return value
		if (turn() == userQuit) {
			cout << "User Quit" << endl;
			return userQuit;
		}
		if (done() == true) {
			cout << player << " won the game " << endl;
			return noErrors;
		}
		if (draw() == true) {
			cout << "After " << numberOfMoves << ", the game is a draw" << endl;
			return endedInDraw;
		}
	}
}