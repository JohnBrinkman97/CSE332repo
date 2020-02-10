#pragma once
#include<string>
using namespace std; 
class TicTacToeGame {
private:
	// 5x5 + label row and column 
	int height = 6; 
	int width = 6;

	string player; // 'X' or 'O'

	//initialize board
	string gameBoard[6][6];

	//coordinates for moves
	unsigned int xCoordinate;
	unsigned int yCoordinate;


public: 
   TicTacToeGame();
	bool done();
	bool draw();
	int prompt(unsigned int &x, unsigned int &y);
	int turn();
	int play();
	string xMoves;
	string oMoves;
	unsigned int numberOfMoves;
	friend std::ostream& operator << (std::ostream& out, const TicTacToeGame& TTT);
};
