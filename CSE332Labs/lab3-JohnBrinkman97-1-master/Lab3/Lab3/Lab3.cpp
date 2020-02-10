// Lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"TicTacToeGame.h"
#include"commonFunctions.h"
#include<iostream>
using namespace std;
int main(int argc, char*argv[])
{
	
	string programInput = argv[inputIndex];
	cout << programInput << endl;
	if(argc != expectedNumberOfArguments || programInput != "TicTacToe"){
	return usageMessage(argv[programNameIndex], "Incorrect command line argument");
	}

	TicTacToeGame T;
	cout << T << endl; // so user can see board before playing
    return T.play();
}

