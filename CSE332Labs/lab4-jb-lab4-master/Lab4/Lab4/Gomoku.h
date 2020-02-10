#pragma once
#include"GameBase.h"
#include<string>
using namespace std;
class GomokuGame : public GameBase {
public:
	string gameBoard[20][20];
//public: 
	GomokuGame();
	virtual int turn();
	virtual bool draw();
	virtual bool done();
	virtual void print();
	string Bmoves;
	string Wmoves;
	friend std::ostream& operator<< (std::ostream& out, const GomokuGame& G);
};