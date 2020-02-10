// Lab4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"commonFunctions.h"
#include"GameBase.h"
#include"Gomoku.h"
#include"TicTacToeGame.h"
#include<memory>

int main(int argc, char * argv[])
{
	if (argc > 2) {
		usageMessage(argv[programNameIndex], "Too many arguments");
		return tooManyArguments;
	}
	if (argc < 2) {
		usageMessage(argv[programNameIndex], "Too few arguments");
		return tooFewArguments;
	}
	try {
	GameBase* game = GameBase::getGame(argc, argv);

	if (game == 0)
	{
		return usageMessage(argv[programNameIndex], "Could not create a game");
	}
	else
	{
		game->print();
		game->play();

		delete game;
	}
}
catch (...) {
	cout << "Bad Alloc Error" << endl;
	return badAlloc;
}
	return noErrors;

}



