
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Required to use strings
#include <stdlib.h> // Required for system()
#include <stdbool.h>
// MAIN LOGIC FUNCTIONS
int startScreen(int);

int validateUserInput(char *out);

void pause(char player[2][100]);

void displayBoard(char player[2][100], bool, int, char playerInput[2][10][10][3]);

void getUserBoatPlacement(char playerData[2][10][10][3], char boardPieces[5][3],
                          char playerName[2][100], int, int boatLength[5]);
// END MAIN LOGIC FUNCTIONS

// ASCII CODE FUNCTIONS
void winScreen_ASCII(int booleanTurn);

void battleShipCover_ASCII();

void battleShipPause_ASCII();
