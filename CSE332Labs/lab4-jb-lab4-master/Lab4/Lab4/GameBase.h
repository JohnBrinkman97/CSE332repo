#pragma once
#include<string>
using namespace std;
class GameBase {
protected:
	int height;
	int width;
	//coordinates for moves
	unsigned int xCoordinate;
	unsigned int yCoordinate;
	string player; 
	unsigned int longestDisplay;
	unsigned int numberOfMoves;

public:
	virtual void print() = 0;
	virtual bool done() = 0;
	virtual bool draw() = 0;
	virtual int turn() = 0;
	int play();
	int prompt(unsigned int &x, unsigned int &y);
	static GameBase * getGame(int argc, char *argv[]);
};