#include "stdafx.h"
#include "TicTacToeGame.h"
#include"commonFunctions.h"
#include<string>
#include<iostream>
#include<sstream>
#include<iomanip>
TicTacToeGame::TicTacToeGame() {
	height = 4;
	width = 4;
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
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


void TicTacToeGame::print() {
	cout << *this << endl;
}