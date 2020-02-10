========================================================================
    CONSOLE APPLICATION : Lab4 Project Overview
========================================================================
John Brinkman Lab 4


test cases: 
player B won in all directions : program printed that B won
player W won in all directions: program printed W won 
Draw: program printed that there was a draw
quit -> program ends and prints "user quit"
Incorrect coordinates works same as previous lab

H:\CSE332\Lab4-github\Lab4\Debug>Lab4.exe TicTacToe Gomoku
Too many arguments
usage: Lab4.exe <game_name>

H:\CSE332\Lab4-github\Lab4\Debug>Lab4.exe
Too few arguments
usage: Lab4.exe <game_name>

possible results from program ending: 
 noErrors = 0 - one of the players won
 wrongNumberOfArguments = 1
 userQuit = 9 (numbers are higher since I used the enum from previous labs)
 inProgress = 10 (never returns, just used)
 endedInDraw = 11 - no winner

 errors -> program only crashed once while testing it - I was using 20 as an index in the array of size 20 
 Had to fix the logic for winning diagonally. Previously, it only tested the two middle crossings