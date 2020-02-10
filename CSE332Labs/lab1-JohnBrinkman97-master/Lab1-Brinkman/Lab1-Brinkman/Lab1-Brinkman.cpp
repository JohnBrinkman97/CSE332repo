// Lab1-Brinkman.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Lab1.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
using namespace std; 
// function declarations
int parseFile(vector<string> &stringVector, char* cString);
int usageMessage(string programName);
int returnValue(errorValues error); //switch statement for errorValues enum 
// main function 
int main(int argc, char* argv[])
{

	// check if exactly one input was given 
	if (argc == expectedNumberOfArguments) {
		vector<string> fromFile;
		vector<int> ints;
		string temp;
		if (parseFile(fromFile, argv[inputFileIndex]) == couldntOpenFile) { // if file cannot be opened
			return returnValue(couldntOpenFile);
		}
		// if file is opened: 
		for (unsigned int i = 0; i < fromFile.size(); ++i) { // iterate through vector of strings from file 
			 temp = fromFile[i];
			 int count = 0; 
			 int digits = temp.size();
			 for (unsigned int j = 0; j < temp.size(); ++j) { // iterate through digits of the string
				 if (isdigit(temp[j])) {
					 count++; // increase count if char is a digit
				 }
			 }
				if (count == digits) { // if all chars are digits
					istringstream iss(temp); //wrap string of all digits in iss
						int k;
					iss >> k; // push iss into an int variable
					ints.push_back(k); // add int value to the int vector 
				}else{
					cout << temp << endl; // if not entirely digits, print it
			}
		}
		for (unsigned int i = 0; i < ints.size(); ++i) {
			cout << ints[i] << endl; // print digits in int vector
		}
		return returnValue(noErrors); // if program completes, return 0 for success
	}
	else {
		// if the wrong number of arguments is entered
		return usageMessage(argv[programNameIndex]);
	}
	
}
int parseFile(vector<string> &stringVector, char* cString ){
	ifstream ifs;
	ifs.open(cString); // open file
	
	if (ifs.is_open()) {
		string temp = "";
		while (ifs >> temp) { // while there are strings left, push them into temp
			stringVector.push_back(temp); // add string to vector
		}
	}
	else {
		return couldntOpenFile; 
	}

	return noErrors;
}
int usageMessage(string programName) { // tell users how to run program 
	cout << "usage: " << programName << " <inputFileName>" << endl;
	return returnValue(wrongNumberOfArguments); // also tell them they put in the wrong number of arguments
}
int returnValue(errorValues error) { // switch statement for possible errors
	errorValues state = error;
	switch (state) {

	case noErrors:
		cout << "Success" << endl;
		break;
	case wrongNumberOfArguments:
		cout << "wrong number of command line arguments" << endl;
		break;
	case couldntOpenFile:
		cout << "couldn't open input file" << endl;
		break;
	}
	return state;

}