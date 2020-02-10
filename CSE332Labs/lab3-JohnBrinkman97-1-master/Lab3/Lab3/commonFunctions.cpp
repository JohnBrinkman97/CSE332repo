#include "stdafx.h"
#include "commonFunctions.h"
#include<iostream>
#include<string>
using namespace std;



int usageMessage(string programName, string errorMessage) { // tell users how to run program 
	cout << errorMessage << endl;
	cout << "usage: " << programName << " TicTacToe" << endl;

	return wrongNumberOfArguments; // also tell them they put in the wrong number of arguments
}
int returnValue(errorValues error) {  // switch statement for possible errors
	errorValues state = error;
	switch (state) {

	case noErrors:
		cout << "Success" << endl;
		break;
	case couldntGetDimensions:
		cout << "Could not find a well formatted dimension line" << endl;
		break;
	case couldntOpenFile:
		cout << "Couldn't open input file" << endl;
		break;

	case couldntFindPieces:
		cout << "Couldn't find any valid pieces in file" << endl;
		break;
	}
	return state;
}
void makeLowercase(string &word) {

	for (unsigned int i = 0; i < word.size(); ++i) {
		if (word[i] >= 65 && word[i] <= 90) {
			word[i] += 32;
		}
	}

}