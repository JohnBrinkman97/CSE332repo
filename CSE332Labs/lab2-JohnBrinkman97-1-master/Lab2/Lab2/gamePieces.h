#pragma once
#include "stdafx.h"
#include "commonFunctions.h"
#include<string>
using namespace std;
enum piece_color{ red = 0,white,black, invalidColor, noColor};

string enumToString(piece_color piece);
piece_color stringToEnum(string color);
struct game_piece {
	piece_color piece;
	string name;
	string display;
};
