//==========================================
// Name: BattleShipCPE223
// Author: Wyatt Bowman
// Date: 11/1/25
// Version: V0.4
// Description: This includes a very basic placement function that allows users to place 1x1 test boats
//              This will also serve as the algorithm for the actual placing of attacks
// Changes: made new function, got rid of not needed comments, going to add lengths in next version
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
void displayBoard(char player[2][100], bool, int, char playerInput[2][10][10][3], char fogPlayerData[2][10][10][3]);
void getUserBoatPlacement(char playerData[2][10][10][3], char fogPlayerData[2][10][10][3], char boardPieces[5][3], char playerName[2][100],
                          int turn);

int main()
{
    //Start Variables
    int userX, userY, mainScreenOption, oldMainScreenOption, rotate, turn = 0;
    int boatLength[5] = {5, 4, 3, 3, 2};

    char playerData[2][10][10][3]; // player, row, column, max size of char
    char fogPlayerData[2][10][10][3]; // player, row, column, max size of char
    char Ships[5][20] = {"Carrier", "Battleship", "Submarine", "Cruiser", "Destroyer"}; // names and such
    char playerName[2][100]; // make smaller in future
    char boardPieces[5][3] = {"AC","BA","CR","SU","DE"};


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
            while(1){ // need win condition

                //TEMP CODE FOR FILLING CELLS WITH EMPTY WATER
                    if(turn == 0){
                        for (int p = 0; p < 2; p++) {
                            for (int i = 0; i < 10; i++) {
                                for (int j = 0; j < 10; j++) {
                                    strcpy(playerData[p][i][j], "  ");
                                        strcpy(fogPlayerData[p][i][j], "  ");
                                }
                            }
                        }
                    }
                //TEMP CODE FOR FILLING CELLS WITH EMPTY WATER

                displayBoard(playerName, screenShake, turn, playerData, fogPlayerData); // just testing output

                if(screenShake){
                    for(int shakeAmount = 0; shakeAmount < 4; shakeAmount++){
                        displayBoard(playerName, shakeAmount % 2 == 0, turn, playerData, fogPlayerData);
                        _sleep(500); //sleep 100ms from windows.h
                    }
                }


                getUserBoatPlacement(playerData, fogPlayerData, boardPieces, playerName, turn);

                scanf("%d");
                turn++;
            }
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

// Function for handling user input and moving around the board

void getUserBoatPlacement(char playerData[2][10][10][3], char fogPlayerInput[2][10][10][3],
                          char boardPieces[5][3], char playerName[2][100], int turn){

    char input = 0, duckedCell[3] = "  ";
    int hori, vert;

    for(int i = 0; i < 5; i++){
        hori = 0; // reset everytime NEED TO MAKE SURE IF USER PLACES BOAT AT ORIGIN WE FILTER FOR THAT
        vert = 0;
        strcpy(duckedCell, playerData[turn][vert][hori]); // copy the default location into the duckedCell
        strcpy(playerData[turn][vert][hori], "[]"); //user cursor

        while(input != 'q'){
            displayBoard(playerName, 0, turn, playerData, fogPlayerInput); // show placement
            printf("\nEnter a direction with W/A/S/D, Q when finished\n");
            scanf(" %c", &input); // space to get rid of any accidental newline stuff

            strcpy(playerData[turn][vert][hori], duckedCell); // put old cell back

            if(input == 'w')
                vert--; // make switch statement later
            else if(input == 's')
                vert++;
            else if(input == 'a')
                hori--;
            else if(input == 'd')
                hori++;
            else if(input != 'q')
                continue; //if user quits they don't have to change the state
            else

            if(vert < 0)
                vert = 0; //checking is user input is valid or not by forcing bounds
            if(vert > 9)
                vert = 9;
            if(hori < 0)
                hori = 0;
            if(hori > 9)
                hori = 9;

            strcpy(duckedCell, playerData[turn][vert][hori]); //store what was there before

            if(strcmp(playerData[turn][vert][hori], "  ") != 0){ //checking the validity of the sqaure
                printf("This Cell is Taken, Try Again!\n");
                _sleep(500); // don't think I actually need this right now
                strcpy(playerData[turn][vert][hori], duckedCell); // put old cell back
                continue;
            }

            strcpy(playerData[turn][vert][hori], "[]"); //user cursor
        }
    strcpy(playerData[turn][vert][hori], boardPieces[i]); // place data
    displayBoard(playerName, 0, turn, playerData, fogPlayerInput); // display
    input = 0; // reset the input so while loop triggers again
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

