#include "stdafx.h"
#include"gamePieces.h"


string colorStrings[5] = { "red", "white", "black", "invalidColor", "noColor" };
	string enumToString(piece_color piece) {
		string temp = colorStrings[piece];
		makeLowercase(temp);
		return temp;
	}
	piece_color stringToEnum(string color) {
		makeLowercase(color);

		if (color == "red") {
			return red;
		}
		else if (color == "black") {
			return black;
		}
		else if (color == "white") {
			return white;
		}
		else if (color.empty()) {
			return noColor;

		}
		else {
			return invalidColor;
		}


	}
