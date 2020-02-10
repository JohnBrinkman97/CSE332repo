// Lab2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "commonFunctions.h"
#include"gameBoard.h"
#include"gamePieces.h"
#include<iostream>
#include<string>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != expectedNumberOfArguments) { // check arguments
		if (argc > expectedNumberOfArguments) {
			usageMessage(argv[programNameIndex], "Too many arguments");
			return tooManyArguments;
		}
		else {
			usageMessage(argv[programNameIndex], "Too few arguments");
			return tooFewArguments;
		}
	}
	else {   //continue with program if number of arguments is correct

		ifstream ifs(argv[inputFileIndex]);

		if (!ifs.is_open()) { // check if file was able to be found and opened
			return returnValue(couldntOpenFile);
		}
		else { // if file is open, continue with program
			unsigned int width;
			unsigned int height;
			if (readInDimensions(ifs, height, width) == couldntGetDimensions) {
				return returnValue(couldntGetDimensions);
			}
			else {
				
				game_piece blankPiece;
				blankPiece.display = " ";
				vector<game_piece> boardVector; 
				for (unsigned int i = 0; i < height*width; ++i) {
					boardVector.push_back(blankPiece);
				}

				if (readInPieces(ifs, boardVector, width, height) != noErrors){
					return couldntFindPieces;
				}
				return printBoard(boardVector, width, height);
			}
		}
	}
}

