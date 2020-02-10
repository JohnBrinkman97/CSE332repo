========================================================================
    CONSOLE APPLICATION : Lab2 Project Overview
========================================================================
Lab1
Author: John Brinkman 

Possible Errors & codes: 

 success = 0 
 wrongNumberOfArguments = 1 (never actually returned from program, just returned from usageMessage function, then a more specific value is returned from program )
 tooManyArguments = 2
 tooFewArguments = 3
 couldntOpenFile = 4
 couldntGetDimensions = 5
 incorrectInputFormat = 6
 couldntFindPieces = 7
 incorrectVectorSize = 8

errors: 
defined an array in a header file, then tried to use it in the cpp file and the compiler gave me an error saying the variable was not defined- I just moved it
attempted to call .size() on a vector that didnt have anything in it yet and the program never stopped running - used the dimension calculation in the loop instead
accidentally called get dimension function twice, so it started getting lines after the dimension line, so the program kept returning as if there were no valid dimensions
