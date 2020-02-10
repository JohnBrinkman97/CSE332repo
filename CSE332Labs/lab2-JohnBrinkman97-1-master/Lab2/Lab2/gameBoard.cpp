#include"stdafx.h"
#include"commonFunctions.h"
#include"gameBoard.h"
#include<iostream>
#include<string>
#include<sstream>
#include<iostream>
using namespace std; 


int readInDimensions(ifstream &file, unsigned int &row, unsigned int &col) {
	string holder;

	while (getline(file, holder)) { // while lines are left, check for dimensions
		istringstream iss(holder);
	
		if (iss >> row && iss >> col) { // check if this action can happen, if it can, do it. Else, return error
			return noErrors;
		}
	}
	
		return couldntGetDimensions;
	
}
int readInPieces(ifstream &file, vector<game_piece> &pieceVector, unsigned int row, unsigned int col) {
	string holder;
	int count = 0;
	while (getline(file, holder)) {
		istringstream iss(holder);
	
		string pieceColor;
		string pieceName;
		string display;
		unsigned int rowPosition;
		unsigned int colPosition;
		iss >> pieceColor;
		iss >> pieceName;
		iss >> display;
		iss >> rowPosition;	
		if (iss >> colPosition) {
			
			piece_color pieceEnum = stringToEnum(pieceColor);
			bool validRow = row >= rowPosition; 
			bool validCol = col >= colPosition;
			
			if (pieceEnum == red || pieceEnum == black || pieceEnum == white && validRow && validCol) {
				
				unsigned int index = col * rowPosition + colPosition;
				pieceVector[index].name = pieceName;
				pieceVector[index].display = display;
				pieceVector[index].piece = pieceEnum;
				++count;
				
			}
		}
	}
	if (count == 0) {
		return returnValue(couldntFindPieces);
	}
	else {
		return noErrors;
	}
}

int printBoard(const vector<game_piece> &pieceVector, unsigned int row, unsigned int col) {
	vector<game_piece> reverseVector = pieceVector;

	reverse(reverseVector.begin(), reverseVector.end());
	if (reverseVector.size() != row * col) {

	
		return incorrectVectorSize;
	}
	for (unsigned int i = 0; i < row; ++i) {
		for (unsigned int j = 0; j < col; ++j) {
			int index = col * i + j;
			cout << reverseVector[index].display << " " << flush;
		}
		cout << endl;
	}
	return noErrors;
}