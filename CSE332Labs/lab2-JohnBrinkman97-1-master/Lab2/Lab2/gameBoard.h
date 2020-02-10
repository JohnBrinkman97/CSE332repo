#pragma once
#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include"gamePieces.h"
#include"commonFunctions.h"
using namespace std; 
int readInDimensions(ifstream &file, unsigned int &row, unsigned int &col);
int readInPieces(ifstream &file, vector<game_piece> &pieceVector, unsigned int row, unsigned int col);
int printBoard(const vector<game_piece> &pieceVector, unsigned int row, unsigned int col);