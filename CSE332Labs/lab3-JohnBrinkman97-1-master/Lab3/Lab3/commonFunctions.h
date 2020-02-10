#pragma once

#include<iostream>
#include<string>
using namespace std;


enum arguments { programNameIndex = 0, inputIndex, expectedNumberOfArguments };
enum errorValues {
	noErrors = 0, wrongNumberOfArguments, tooManyArguments, tooFewArguments, couldntOpenFile, couldntGetDimensions, incorrectInputFormat, couldntFindPieces, incorrectVectorSize, userQuit, inProgress,endedInDraw
};
int usageMessage(string programName, string errorMessage);  // tell users how to run program 

int returnValue(errorValues error);  // switch statement for possible errors (not used in lab3)

void makeLowercase(string &word); //not used in lab3