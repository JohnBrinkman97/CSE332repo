#include "stdafx.h"
#include "TicTacToeGame.h"
#include"commonFunctions.h"
#include"Gomoku.h"
#include<string>
#include<iostream>
#include<sstream>
#include<iomanip>
using namespace std;
GomokuGame::GomokuGame() {
	height =20;
	width = 20;
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			gameBoard[i][j] = " ";
		}
	}
	
	gameBoard[1][0] = "1";
	gameBoard[2][0] = "2";
	gameBoard[3][0] = "3";
	gameBoard[4][0] = "4";
	gameBoard[5][0] = "5";
	gameBoard[6][0] = "6";
	gameBoard[7][0] = "7";
	gameBoard[8][0] = "8";
	gameBoard[9][0] = "9";
	gameBoard[10][0] = "10";
	gameBoard[11][0] = "11";
	gameBoard[12][0] = "12";
	gameBoard[13][0] = "13";
	gameBoard[14][0] = "14";
	gameBoard[15][0] = "15";
	gameBoard[16][0] = "16";
	gameBoard[17][0] = "17";
	gameBoard[18][0] = "18";
	gameBoard[19][0] = "19";
	gameBoard[0][0] = "X";
	gameBoard[0][1] = "1";
	gameBoard[0][2] = "2";
	gameBoard[0][3] = "3";
	gameBoard[0][4] = "4";
	gameBoard[0][5] = "5";
	gameBoard[0][6] = "6";
	gameBoard[0][7] = "7";
	gameBoard[0][8] = "8";
	gameBoard[0][9] = "9";
	gameBoard[0][10] = "10";
	gameBoard[0][11] = "11";
	gameBoard[0][12] = "12";
	gameBoard[0][13] = "13";
	gameBoard[0][14] = "14";
	gameBoard[0][15] = "15";
	gameBoard[0][16] = "16";
	gameBoard[0][17] = "17";
	gameBoard[0][18] = "18";
	gameBoard[0][19] = "19";
	
	player = "W"; //black goes first so when it gets to turn, this will be switched



}

bool GomokuGame::done() {
	
	for (int i = 1; i < 19; ++i) { //horizontal
		int count = 0;
		for (int j = 1; j < 18; ++j) {
		
			if (gameBoard[i][j] == gameBoard[i][j + 1] && gameBoard[i][j] != " ") {
				++count;
			
			}
			if (count == 4) { // 4 pairs = 5 in a row
				return true;
			}
		}
	}
	for (int j = 1; j < 18; ++j) {
		int count = 0;
		for (int i = 1; i < 19; ++i) { //veritcal;
			
			if (gameBoard[j][i] == gameBoard[j+1][i] && gameBoard[i][j] != " ") {
				++count;
				
			}
			if (count == 4) { 
				
				return true;
			}
		}
	}
	int count = 0;

	for (int i = 1; i < 19-5; i++) {
		for (int j = 1; j < 19 - 5; j++) {
			for (int k = 0; k < 5; k++) {
				
				if (gameBoard[j][i] == gameBoard[j + k][i + k] && gameBoard[j][i] != " ") {
					++count;
					if (count == 5) {
						return true;
					
					}
				}
				else {
					count = 0;
				}
			}
		}
	}
	count = 0;
	for (int i = 1; i < 19 - 5; i++) {
		for (int j = 19; j > 5; j--) {
			for (int k = 0; k < 5; k++) {
				
				if (gameBoard[i][j] == gameBoard[i + k][j - k] && gameBoard[i][j] != " ") {
					++count;
					if (count == 5) {
						return true;
					}
				}
				else {
					count = 0;
				}
			}
		}
	}

	return false;
}
bool GomokuGame::draw() {
	if (numberOfMoves == 361) {
		return true;
	}
	for (int i = 1; i < 19; ++i) {
		int count = 0;
		for (int j = 1; j < 18; ++j) {
			if (gameBoard[i][j] == gameBoard[i][j + 1] || gameBoard[i][j] == " ") {
				++count;
			}
			if (count == 5) {
				return false;
			}
		}
	}
	for (int i = 1; i < 19; ++i) {
		int count = 0;
		for (int j = 1; j < 18; ++j) {
			if (gameBoard[j][i] == gameBoard[j + 1][i] || gameBoard[i][j] == " ") {
				++count;
			}
			if (count == 5) {
				return false;
			}
		}
	}

	int count = 0;

	for (int i = 1; i < 19 - 5; i++) {
		for (int j = 1; j < 19 - 5; j++) {
			for (int k = 0; k < 5; k++) {
			
				if (gameBoard[j][i] == gameBoard[j + k][i + k] || gameBoard[j+k][i+k] == " ") {
					++count;
					if (count == 5) {
						return false;
						
					}
				}
				else {
					count = 0;
				}
			}
		}
	}
	count = 0;
	for (int i = 1; i < 19 - 5; i++) {
		for (int j = 19; j > 5; j--) {
			for (int k = 0; k < 5; k++) {
				if (gameBoard[i][j] == gameBoard[i + k][j - k] || gameBoard[i + k][j + k] == " ") {
					++count;
					if (count == 5) {
						return false;
					}
				}
				else {
					count = 0;
				}
			}
		}
	}
	return true;

}

int GomokuGame::turn() {
	if (player == "B") { //switch player
		player = "W";
	}
	else {
		player = "B";
	}
	cout << "Player " << player << "'s turn" << endl << endl;
	unsigned int tempX;
	unsigned int tempY;

	while (inProgress) { // loop until noErrors
		if (prompt(xCoordinate, yCoordinate) == userQuit) {
			return userQuit;
		}

		tempX = xCoordinate;

	
		tempY = yCoordinate;
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
	if (player == "B") {
		Bmoves += move;
		cout << "Player " << player << ": " << Bmoves << endl << endl;

	}
	else {
		Wmoves += move;
		cout << "Player " << player << ": " << Wmoves << endl << endl;

	}

	return noErrors;
}



void GomokuGame::print() {
	cout << *this << endl;
}

ostream& operator<< (std::ostream& out, const GomokuGame& G) {

	for (int i = 19; i >= 0; --i) {
		if (i < 10) {
			cout << " " << flush;
		}
		for (int j = 0; j < 20; ++j) {
			if (j > 9 && i > 0) {
				cout << " ";
			}
			cout << G.gameBoard[i][j] << " ";
		}
		cout << endl;
	}
	return out;
}