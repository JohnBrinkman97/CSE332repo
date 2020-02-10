#pragma once
#include<iostream>
#include<string>
using namespace std;


enum arguments { programNameIndex = 0, inputFileIndex, expectedNumberOfArguments };
enum errorValues {
	noErrors = 0, wrongNumberOfArguments, tooManyArguments,tooFewArguments, couldntOpenFile, couldntGetDimensions, incorrectInputFormat,couldntFindPieces,incorrectVectorSize
};
int usageMessage(string programName, string errorMessage);  // tell users how to run program 

int returnValue(errorValues error);  // switch statement for possible errors
	
void makeLowercase(string &word);