//==========================================
// Name: BattleShipCPE223
// Author: Wyatt Bowman
// Date: 11/1/25
// Version: V0.3
// Description: This includes a prototype of the front end code
// Changes: Everything changed
//==========================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Required to use strings
#include <stdlib.h> // Required for system()
#include <stdbool.h>


int setBoats(int, int, int, int);
int startScreen(int);
void showBoard(); // declaring function that shows board
void battleShipCover_ASCII();
void displayBoard(char player[2][100], bool, int, char playerInput[2][10][10][3], char fogPlayerInput[2][10][10][3]);

int BattleArray[11][11] = {0}; // declaring array, indexing starts with one

int main()
{
    //Start Variables
    int userX, userY, mainScreenOption, oldMainScreenOption, rotate, turn;

    char playerData[2][10][10][3]; // player, row, column, max size of char
    char fogPlayerData[2][10][10][3]; // player, row, column, max size of char
    char Ships[5][20] = {"Carrier", "Battleship", "Submarine", "Cruiser", "Destroyer"}; // names and such
    char playerName[2][100]; // make smaller in future
    char boardPieces[5][3] = {"AC","BA","CR","SU","DE"};

    /*
    UNTIL WE GET USER DATA FOR BOARD FILLING WITH STUFF
    */
    for (int p = 0; p < 2; p++) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                strcpy(playerData[p][i][j], "AB");
                strcpy(fogPlayerData[p][i][j], "FG");
            }
        }
    }
    /*
    UNTIL WE GET USER DATA FOR BOARD FILLING WITH STUFF
    */


    bool screenShake = 0; // FOR GAME NEEDS TO BE DYNAMIC
    //End Variables

    while(mainScreenOption != 0){ // change to when user enters new line then quits
        battleShipCover_ASCII(); // ASCII ART from void function
        startScreen(mainScreenOption);
        oldMainScreenOption = mainScreenOption;
        scanf("%d", &mainScreenOption); // user input for the options
        system("cls"); // clears terminal
    }

    switch(oldMainScreenOption){

        case 1: // PLAY GAME
            scanf("%*[^\n]");  // Skip characters until newline
            scanf("%*c");      // Consume the newline

                for(int playerNumber = 0; playerNumber < 2; playerNumber++){ // getting the usernames of each player
                    printf("\t\t\n\nWhat is the name of Player %d?:\t\n\n", playerNumber + 1);
                    fgets(playerName[playerNumber], sizeof(playerName[playerNumber]), stdin);
                    int length = strlen(playerName[playerNumber]); // bad practice fix later
                    playerName[playerNumber][length - 1] = '\0'; // making sure the last real character isn't a newline
                }

            turn = 0;

            while(1){ // need win condition
                displayBoard(playerName, screenShake, turn, playerData, fogPlayerData); // just testing output
                if(screenShake){
                    for(int shakeAmount = 0; shakeAmount < 4; shakeAmount++){
                        displayBoard(playerName, shakeAmount % 2 == 0, turn, playerData, fogPlayerData);
                        _sleep(500); //sleep 100ms from windows.h
                    }
                }
                scanf("%d");
                turn++;
            }

/*
        // This code is just for develpoment
        for(int i = 0; i <= 10; i++){ // fill with zeros and creating margins
            printf("\n\n");
            for(int j = 0; j <= 10; j++){

                if(i == 0){
                    BattleArray[i][j] = j;
                } else if (j == 0){
                BattleArray[i][j] = i;
                } else{
                BattleArray[i][j] = 0;
                }

                printf("%d  ", BattleArray[i][j]);
            }

        }



        printf("\n");
        for(int boat = 0; boat <= 4; boat++){
            printf("Where do you want your %s to start in the X:    ", Ships[boat]); // literally just going to assume bottom corner and horizontally for now
            scanf("%d", &userX);
            printf("Where do you want your %s to start in the Y:    ", Ships[boat]); // Y coord
            scanf("%d", &userY);
            printf("Do you want your piece Vertically: "); // one for vertical, in future take more input
            scanf("%d", &rotate);
            printf("\n");
            setBoats(userX, userY, boat, rotate); // boats to control index of the actual piece
        }
        showBoard(); // Showing the board

        while(1){} // THIS IS TEMP PLEASE DON'T LEAVE THIS WILL BREAK COMPUTER OVER TIME
*/



        break;
        case 2: // HELP OPTION
            printf("\n\nVisit \"https://www.wikihow.com/Play-Battleship\" for more information\n\n");
        break;
        case 3: // CREDITS
            printf("\n\nDeveloped by Wyatt Bowman and Kieran Cavanagh\n\n");
        break;

        default:
            printf("Invalid Input, Try again");
    }

    return 0;

}

// END MAIN









// START USER DEFINED FUNCTIONS

// Basic Function to Set Boats down

int setBoats(int xCoord, int yCoord, int boatIndex, int orientation){ //placing boats

    int length[5] = {5, 4, 3, 3, 2}; // lengths of each piece

    if(orientation == 1){
        for (int iVert = 0; iVert < length[boatIndex]; iVert++) {
            BattleArray[yCoord + iVert][xCoord] = 1; // placing boats in array with size
        }
    }else if(orientation == 0){
        for (int iHor = 0; iHor < length[boatIndex]; iHor++) {
            BattleArray[yCoord][xCoord + iHor] = 1; // placing boats in array with size
        }
    }
    return 1;
}

// Function to print the selection screen

int startScreen(int option){ // main screen code, helps select and change user input
    printf("\n\n\n\t\t\t   Pick an option (1-3)\n\n");

    if(option == 1) // option 1
        printf("\t\t\t     >>>Play Game!<<<\n\n");
    else
        printf("\t\t\t\tPlay Game!\n\n");

    if(option == 2) // option 2
        printf("\t\t\t     >>>Help<<<\n\n");
    else
        printf("\t\t\t\tHelp\n\n");

    if(option == 3) // option 3
        printf("\t\t\t     >>>Credits<<<\n\n");
    else
        printf("\t\t\t\tCredits\n\n");

    printf("\t\t\t  Press \"0\" When Selected\n");

    return 1;
}

// Void Functions

// Function to display the board with improved GUI

void displayBoard(char player[2][100], bool screenShake, int turn, char playerInput[2][10][10][3], char fogPlayerInput[2][10][10][3]){
    system("cls"); // clears terminal
    int booleanTurn = turn % 2;
    printf("\n\tPlayer %d's Board: %-50sFog of War\n\n", booleanTurn + 1, player[booleanTurn]); // header display, using fixed width Field

        for (int j = 0; j < 10; j++) // current player line
            printf("+----");
        printf("+\t"); // print the last line and tab over for second grid

        for (int j = 0; j < 10; j++) // opponent player line
            printf("+----");
        printf("+\n"); // Print vertical sides of each cell


    for (int i = 0; i < 10; i++) {// Print top border of each cell
        if(screenShake && (i % 2 == 0)) // screenshake code
            printf("  "); // 2 space offset for the screenshake

        for (int j = 0; j < 10; j++) // current players line
            printf("| %s ", playerInput[booleanTurn][i][j]);
        printf("|\t"); // Print vertical sides of each cell

        for (int j = 0; j < 10; j++)  // opponent players lines
            printf("| %s ", fogPlayerInput[booleanTurn][i][j]);
        printf("|\n");

        if(screenShake && (i % 2 == 0)) // screenshake code
            printf("  "); // 2 space offset for the screenshake

        // note to self, insert data on the second for loop somewhere in the middle, workout line spacing and such later.
        for (int j = 0; j < 10; j++) // Print bottom border of the last row
            printf("+----");
        printf("+\t"); // last line for the current players layout

        for (int j = 0; j < 10; j++) // Print bottom border of the last row
            printf("+----");
        printf("+\n"); // last "+" before newline
    }
    //printf("\nScore: %d\n", score); //change for later
}



// Function to show the data board, only needed for development

void showBoard(){ // shows board, makes sense ig
    system("cls"); // clears terminal
for(int i = 0; i <= 10; i++){
        printf("\n\n");
        for(int j = 0; j <= 10; j++){
             printf("%d  ", BattleArray[i][j]);
        }
    }
}

// ASCII ART START HERE

void battleShipCover_ASCII(){
    printf("    ______     ______     ______   ______   __         ______    \n");
    printf("   /\\  == \\   /\\  __ \\   /\\__  _\\ /\\__  _\\ /\\ \\       /\\  ___\\   \n");
    printf("   \\ \\  __<   \\ \\  __ \\  \\/_/\\ \\/ \\/_/\\ \\/ \\ \\ \\____  \\ \\  __\\   \n");
    printf("    \\ \\_____\\  \\ \\_\\ \\_\\    \\ \\_\\    \\ \\_\\  \\ \\_____\\  \\ \\_____\\ \n");
    printf("     \\/_____/   \\/_/\\/_/     \\/_/     \\/_/   \\/_____/   \\/_____/ \n");
    printf("                   ______     __  __     __     ______           \n");
    printf("                  /\\  ___\\   /\\ \\_\\ \\   /\\ \\   /\\  == \\          \n");
    printf("                  \\ \\___  \\  \\ \\  __ \\  \\ \\ \\  \\ \\  _-/          \n");
    printf("                   \\/\\_____\\  \\ \\_\\ \\_\\  \\ \\_\\  \\ \\_\\            \n");
    printf("                    \\/_____/   \\/_/\\/_/   \\/_/   \\/_/            \n");
}
