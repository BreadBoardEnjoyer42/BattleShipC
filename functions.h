#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include <stdbool.h>

#define MAX_SIZE 15
#define MIN_SIZE 5
extern int size; // size of board value
extern int playerPoints[2];
extern int CHECK[2][15][15];


// MAIN LOGIC FUNCTIONS
int startScreen(int);

int validateUserInput(char *out);

int validateUserInputInt(int *out);

void pause();

void displayBoard(char player[2][31], bool screenShake, int booleanTurn, int playerInput[2][15][15], char shipValueAbrv[14][5]);

void printPlayerBoardRow(int player,int row,int playerInput[2][15][15],char shipValueAbrv[14][5]);

void printPlayerFogBoardRow(int player,int row,int playerInput[2][15][15],char shipValueAbrv[14][5]);

void getUserBoatPlacement(int playerData[2][15][15], char playerName[2][31], int turn, int boatLength[5],
                          int shipValueType[5], char shipValueAbrv[14][5], char ships[5][20]);
void transistion(int);

void attackSmack(int turn, int playerData[2][15][15], char playerName[2][31], char shipValueAbrv[14][5],
                bool *screenShake, bool airStrikeMode);

int getSize(int *sizeF);

void displayBoardHeader(int booleanTurn, char player[2][31]);

void findEmptyCell(int playerData[2][15][15], int *hori, int *vert, int booleanTurn);

void winCondition(int playerData[2][15][15], int booleanTurn);

void getMode(bool *airStrikeMode);


// ASCII CODE FUNCTIONS
void winScreen_ASCII(int booleanTurn);

void battleShipCover_ASCII();

void battleShipPause_ASCII();

void inbetweenScreen();

void titleScreen();

void surrender();

#endif // FUNCTIONS_H_INCLUDED
