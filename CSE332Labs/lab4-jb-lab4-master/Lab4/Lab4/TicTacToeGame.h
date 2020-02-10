
#pragma once
#include<string>
#include"GameBase.h"
#include"commonFunctions.h"
using namespace std; 
class TicTacToeGame: public GameBase {
private: 
	//coordinates for moves
	unsigned int xCoordinate;
	unsigned int yCoordinate;
	string gameBoard[6][6];

public: 
    TicTacToeGame();
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	string xMoves;
	string oMoves;
	
	virtual void print();
	friend std::ostream& operator << (std::ostream& out, const TicTacToeGame& TTT);
};
