
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Required to use strings
#include <stdlib.h> // Required for system()
#include <stdbool.h>

#include "functions.h"


//Function for getting valid user input
int validateUserInput(char *out){
    char line[128];  // 16 byte
    if(!fgets(line, sizeof(line), stdin)) // validating string for sscanf
       return 0; // EXIT_SUCCESS

    char value, bufferCheck;
    static int pCheck = 1;// for using P as a toggle and static so it keeps its value

    if(sscanf(line, " %c %c", &value, &bufferCheck) == 1){
        *out = value;
        if(value == 'p' || value == 'P'){
            pCheck++;
                if(!(pCheck % 2)){ // TOGGLE FUNCTION
                    pause();
                }
        }
        return 1; // EXIT_FAILURE
    }
    return 0;
}

int validateUserInputInt(int *out){
    char line[128];  // 16 byte
    if(!fgets(line, sizeof(line), stdin)) // validating string for sscanf
       return 0; // EXIT_SUCCESS

    int value;
    char bufferCheck;
    static int pCheck = 1;// for using P as a toggle and static so it keeps its value

    if(sscanf(line, " %d %c", &value, &bufferCheck) == 1){
        *out = value;
        if(value == 'p' || value == 'P'){
            pCheck++;
                if(!(pCheck % 2)){ // TOGGLE FUNCTION
                    pause();
                }
        }
        return 1; // EXIT_FAILURE
    }
    return 0;
}
// END Function for validating user input



//Start Screen Function for user input
int startScreen(int option){ // main screen code, helps select and change user input
    printf("\n\n\n\t\t\t   Select Using W and S \n\n");

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

    printf("\t\t\t  Press \"q\" When Selected\n");

    return 1;
}
//END Start Screen Function



// Display Board Function to show the board with improved GUI
void displayBoard(char player[2][100], bool screenShake, int booleanTurn, int playerInput[2][20][20],
                  char shipValueAbrv[14][5]){
    system("cls"); // clears terminal
    displayBoardHeader(booleanTurn, player); // For centering the headers for the fog of war and player data because board is variable

        for (int j = 0; j < size; j++) // current player line
            printf("+----");
        printf("+\t"); // print the last line and tab over for second grid

        for (int j = 0; j < size; j++) // opponent player line
            printf("+----");
        printf("+\n"); // Print vertical sides of each cell

    for (int i = 0; i < size; i++) {// Print top border of each cell
        if(screenShake && (i % 2 == 0)) // screenshake code
            printf("  "); // 2 space offset for the screenshake

        printPlayerBoardRow(booleanTurn,i,playerInput,shipValueAbrv);
        printf("\t"); // Print vertical sides of each cell
        printPlayerFogBoardRow(booleanTurn,i,playerInput,shipValueAbrv);
        printf("\n");

        if(screenShake && (i % 2 == 0)) // screenshake code
            printf("  "); // 2 space offset for the screenshake

        // note to self, insert data on the second for loop somewhere in the middle, workout line spacing and such later.
        for (int j = 0; j < size; j++) // Print bottom border of the last row
            printf("+----");
        printf("+\t"); // last line for the current players layout

        for (int j = 0; j < size; j++) // Print bottom border of the last row
            printf("+----");
        printf("+\n"); // last "+" before newline
    }
}

void printPlayerBoardRow(int player,int row,int playerInput[2][20][20],char shipValueAbrv[14][5]){
    for (int col = 0; col < size; col++){
        printf("|");
        int v = playerInput[player][row][col];
        if (v < 0 || v >= 14) {
            printf("??  "); // fallback idk im troubleshooting here
        } else {
            printf("%s", shipValueAbrv[v]);
        }

    }
    printf("|");
}

void printPlayerFogBoardRow(int player,int row,int playerInput[2][20][20],char shipValueAbrv[14][5]){
    for (int col = 0;col < size; col++){
        printf("|");
        if (playerInput[player][row][col]==1){
            printf("Miss");
        }
        else if ((playerInput[player][row][col])%2){
            printf(" XX ");
        }
        else{
            printf(" ~~ ");
        }
    }
    printf("|");
}
// END Display Board Function



// Handling User Input for Boat Placement Function
void getUserBoatPlacement(int playerData[2][20][20], char playerName[2][100], int turn,
                          int boatLength[5], int shipValueType[5],char shipValueAbrv[14][5],
                          char ships[5][20]){

    char input, orientation;
    int hori = 0, vert = 0, newVert, newHori, prevLocation = 0;
    bool valid;

    for(int i = 0; i < 5; i++){
        selectionStart:
        input = 0; // reset the input so while loop triggers again
        findEmptyCell(playerData, &hori, &vert, turn);
        newHori = hori;
        newVert = vert;
        prevLocation = playerData[turn][vert][hori]; //copy into temp variable

        playerData[turn][vert][hori] = 12; //user cursor

        while(!((input=='q')||(input=='Q'))){
            displayBoard(playerName, 0, turn, playerData, shipValueAbrv); // show placement
            printf("\nEnter a direction with W/A/S/D, Q when finished\n");

            while(!validateUserInput(&input)){ // running validation check for user input
                printf("Invalid Input");
            }

            playerData[turn][vert][hori] = prevLocation; // put old cell back

            if(input == 'w' || input == 'W')
                newVert--; // make switch statement later
            else if(input == 's' || input == 'S')
                newVert++;
            else if(input == 'a' || input == 'A')
                newHori--;
            else if(input == 'd' || input == 'D')
                newHori++;
            else if(input != 'q')
                continue; //if user quits they don't have to change the state

            if(newVert < 0)
                newVert = size - 1; //checking is user input is valid or not by forcing bounds
            if(newVert > size - 1)
                newVert = 0;
            if(newHori < 0)
                newHori = size - 1;
            if(newHori >  size - 1)
                newHori = 0;

            playerData[turn][vert][hori] = prevLocation; // erase old cursor
            vert = newVert;
            hori = newHori;
            prevLocation = playerData[turn][vert][hori];
            playerData[turn][vert][hori] = 12; //user cursor
        }

        printf("Place Boat %s (Length %d). Enter H for horizontal and V for vertical\n", ships[i], boatLength[i]);
        playerData[turn][vert][hori] = prevLocation; // SLAP SLAP

        while(!validateUserInput(&orientation)){ // running validation check for user input
            printf("Invalid Input");
        }
        valid = false; // checking for validity

        while(!valid){
            valid = true; // only changes if invalid
            for(int k = 0; k < boatLength[i]; k++){ // CHECKING BEFORE PLACING
                // If triggered on V and H then need escape sequence
                if(orientation == 'V' || orientation == 'v'){
                    if((vert + boatLength[i]) > size){
                        valid = false;
                        break;
                    }
                    if(playerData[turn][vert + k][hori] != 0){
                        valid = false;
                        break;
                    }
                }
                else if(orientation == 'H' || orientation == 'h'){
                    if((hori + boatLength[i]) > size){
                        valid = false;
                        break;
                    }
                    if(playerData[turn][vert][hori + k] != 0){
                        valid = false;
                        break;
                    }
                }
                else{ //invalid input and not invalid placement
                    valid = false;
                    break;
                }
            }
            if (!valid){
                printf("Invalid Input Try Again or Type 'X' if Stuck\n"); //getting user input and trying again
                while(validateUserInput(&orientation) != 1){ // running validation check for user input
                    printf("Invalid Input");
                }
                if(orientation == 'X' || orientation == 'x'){ // resets values
                    playerData[turn][vert][hori]=prevLocation;
                    goto selectionStart; // GOING BACK TO SELECTION
                }
            }
        }
        for(int j = 0; j < boatLength[i]; j++){ // place boats now
            if((orientation == 'V') || (orientation == 'v')){
                playerData[turn][vert + j][hori] = shipValueType[i]; // place data
            }
            else if (orientation == 'H' || orientation == 'h'){
                playerData[turn][vert][hori + j] = shipValueType[i]; // place data
            }
        }
        displayBoard(playerName, 0, turn, playerData, shipValueAbrv); // display
    }
}
// END Handling User Input for Boat Placement Function



// Pause Function Prototype
void pause(){
    system("cls");
    char pauseIn;
    battleShipPause_ASCII();
    printf("\n\n\nEnter anything except 'L' or 'P' to Unpause \n\n"); // MAKE TOGGLE
    printf("If player would like to surrender, enter 'L'");

    while(pauseIn != 'p' && pauseIn != 'P'){
        while(!validateUserInput(&pauseIn)){ // running validation check for user input
            printf("Invalid Input");
        }
        if(pauseIn == 'L' || pauseIn == 'l'){
            printf("Don't give up now! We haven't developed a way for you to lose :\ ");
        }
    }
        // INSERT WIN CONDITION WILL NEED TO USE POINTER TO ACCESS AND CHANGE
}
// END Pause Function Prototype

void transistion(int booleanTurn){
    char userInput = 0;
    while((userInput != 'y') && (userInput != 'Y')){
        system("cls");
        inbetweenScreen();
        printf("\n\t\t\tIs Player %d Ready to Play? (ENTER Y IF SO)\n", booleanTurn + 1);
        while(validateUserInput(&userInput) != 1){ // running validation check for user input
            printf("Invalid Input");
        }
    }

}



void attackSmack(int turn, int playerData[2][20][20], char playerName[2][100], char shipValueAbrv[14][5],
                bool *screenShake){
    selectionStart:

    char input, orientation;
    int newCol, newRow, prevLocation;
    bool valid;
    int attackRow = 0;
    int attackCol = 0;
    int scoreArray[5];
    static int CHECK[2][20][20] = {0}; // static so its not redefined every time

    input = 0; // reset the input so while loop triggers again
    newRow = attackRow;
    newCol = attackCol;

    prevLocation = playerData[turn][attackRow][attackCol]; //copy into temp variable

        while(!((input == 'q')||(input == 'Q'))){
            displayBoard(playerName, 0, turn, playerData, shipValueAbrv); // show placement
            printf("\nPlace your Attack with W/A/S/D, Q when finished\n");
            while(!validateUserInput(&input)){ // running validation check for user input
            printf("Invalid Input\n");
            }

            playerData[turn][attackRow][attackCol] = prevLocation;

            if(input == 'w' || input == 'W')
                newRow--; // make switch statement later
            else if(input == 's' || input == 'S')
                newRow++;
            else if(input == 'a' || input == 'A')
                newCol--;
            else if(input == 'd' || input == 'D')
                newCol++;
            else if(input != 'q')
                continue; //if user quits they don't have to change the state

            if(newCol < 0)
                newCol = size - 1; //checking is user input is valid or not by forcing bounds
            if(newCol > size - 1)
                newCol = 0;
            if(newRow < 0)
                newRow = size - 1;
            if(newRow > size - 1)
                newRow = 0;
            /*
            if(playerData[turn][newRow][newCol] % 12 != 0){ //checking the validity of the square
                printf("This Cell is Taken, Try Again!\n");
                continue;
            }
            */
            attackCol = newCol;
            attackRow = newRow;
            prevLocation = playerData[turn][attackRow][attackCol];
            playerData[turn][attackRow][attackCol] = 12 ; //user cursor

        }
            playerData[turn][attackRow][attackCol] = prevLocation;
            if(CHECK[turn][newRow][newCol] == 0){
                playerData[(!turn)][newRow][newCol] += 1;
                if(playerData[(!turn)][newRow][newCol] % 2 == 1 && playerData[(!turn)][newRow][newCol] > 2){
                    *screenShake = true;
                }
                CHECK[turn][newRow][newCol]++;
            }
            //displayBoard(playerName, 0, turn, playerData, shipValueAbrv); // display
}

int getSize(int *sizeF){
    int count = 0, out = 0;
    printf("What size would you like the board to be?\n");

    while(out > MAX_SIZE || out < MIN_SIZE){
        if(count != 0){
            printf("\nPlease stay between the bounds of %d and %d\n", MAX_SIZE, MIN_SIZE);
        }

        while(!validateUserInputInt(&out)){ // running validation check for user input
                printf("Invalid Input\n");
        }
        *sizeF = out;
        count++;
    }
    return 1;
}


void displayBoardHeader(int booleanTurn, char player[2][100]) {
    int gridWidth = size * 5 + 1;  // width of one grid
    int sizePlayerOffset = strlen("Player #'s Board: ") + strlen(player[booleanTurn]); // how long is said string
    int sizeFogOffset = strlen("Fog of War");
    printf("\n");
    for(int y = (gridWidth/2 - sizePlayerOffset/2); y > 0; y--){ // add spaces for half the length of the grid AND half the string
        printf(" ");
    }
    printf("Player %d's Board: %s", booleanTurn + 1 , player[booleanTurn]);
    for(int y = (gridWidth - sizePlayerOffset + sizeFogOffset/2) + 5; y > 0; y--){ // same algorithm
        printf(" ");
    }
    printf("Fog of War\n");

}

void findEmptyCell(int playerData[2][20][20], int *hori, int *vert, int booleanTurn){
        while(playerData[booleanTurn][*vert][*hori] != 0){ // CHECKING TO SEE THE NEXT VALID PLACE TO PUT THE CURSOR
            (*hori)++;
            if((*hori) >= size){ // IF MAX THEN GO DOWN A LINE
                (*vert)++; // change vertically
                *hori = 0; // back to 0th x index
                continue;
            }
        }
}

void winCondition(int playerData[2][20][20], int booleanTurn, int points[2]){
    int pointNumber[5] = {1000, 750, 500, 500, 100};
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(playerData[(!booleanTurn)][i][j] % 2 == 1 && playerData[(!booleanTurn)][i][j] > 2){
                for(int k = 1; k < 5; k++){
                    if(!(playerData[(!booleanTurn)][i][j] % (2*k+1))){
                        points[booleanTurn] += pointNumber[k];
                    }
                }
            }
        }
    }
}







