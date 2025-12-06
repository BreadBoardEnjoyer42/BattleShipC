#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include <stdbool.h>

#define MAX_SIZE 25
#define MIN_SIZE 5
extern int size; // size of board value


// MAIN LOGIC FUNCTIONS
int startScreen(int);

int validateUserInput(char *out);

int validateUserInputInt(int *out);

void pause();

void displayBoard(char player[2][100], bool screenShake, int booleanTurn, int playerInput[2][20][20], char shipValueAbrv[14][5]);

void printPlayerBoardRow(int player,int row,int playerInput[2][20][20],char shipValueAbrv[14][5]);

void printPlayerFogBoardRow(int player,int row,int playerInput[2][20][20],char shipValueAbrv[14][5]);

void getUserBoatPlacement(int playerData[2][20][20], char playerName[2][100], int turn, int boatLength[5],
                          int shipValueType[5], char shipValueAbrv[14][5], char ships[5][20]);
void transistion(int);

void attackSmack(int turn, int playerData[2][20][20], char playerName[2][100], char shipValueAbrv[14][5]);

int getSize(int *sizeF);

void displayBoardHeader(int booleanTurn, char player[2][100]);


// ASCII CODE FUNCTIONS
void winScreen_ASCII(int booleanTurn);

void battleShipCover_ASCII();

void battleShipPause_ASCII();

void inbetweenScreen();

void titleScreen();

#endif // FUNCTIONS_H_INCLUDED
