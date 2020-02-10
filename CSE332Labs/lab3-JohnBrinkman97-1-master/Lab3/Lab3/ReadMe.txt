========================================================================
    CONSOLE APPLICATION : Lab3 Project Overview
========================================================================

John Brinkman
Lab3

test cases: 
player X won in all directions : program printed that X won
player O won in all directions: program printed O won 
Draw: program printed that there was a draw
quit -> program ends and prints "user quit"
4,4 -> incorrect format or board position (only middle 3x3 is playable)
user form: #,# 
333 as coordinate -> incorrect format or board position (only middle 3x3 is playable)
user form: #,#
3   3 as coordinate -> I can't figure out why the error prints twice... Program still functions after, just annoying that it prints twice
"wqf" as coordinate -> incorrect format or board position (only middle 3x3 is playable)
user form: #,#

possible results from program ending: 
 noErrors = 0 - one of the players won
 wrongNumberOfArguments = 1
 userQuit = 9 (numbers are higher since I used the enum from previous labs)
 inProgress = 10 (never returns, just used)
 endedInDraw = 11 - no winner

 errors -> program never crashed while testing it,
  but I was using incorrect column dimensions so there was no winner when a player got 3 in a row vertically
  I kept getting a build error since I would forget to end the program before building 
