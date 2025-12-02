#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "functionsDecl.c"

//Function for getting valid user input
int validateUserInput(char *out){
    char line[128];  // 16 byte
    if(!fgets(line, sizeof(line), stdin))
       return 0; // EXIT_SUCCESS

    char value, bufferCheck;

    if(sscanf(line, " %c %c", &value, &bufferCheck) == 1){
        *out = value;
        return 1; // EXIT_FAILURE
    }
    return 0;
}
// END Function for validating user input



//Start Screen Function for user input
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
//END Start Screen Function



// Display Board Function to show the board with improved GUI
void displayBoard(char player[2][100], bool screenShake, int turn, char playerInput[2][10][10][3]){
    system("cls"); // clears terminal
    printf("\n\tPlayer %d's Board: %-50sFog of War\n\n", turn + 1, player[turn]); // header display, using fixed width Field

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
            printf("| %s ", playerInput[turn][i][j]);
        printf("|\t"); // Print vertical sides of each cell

        for (int j = 0; j < 10; j++)  // opponent players lines
            printf("| %s ", playerInput[turn][i][j]);
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
}
// END Display Board Function


// Handling User Input for Boat Placement Function
void getUserBoatPlacement(char playerData[2][10][10][3],
                          char boardPieces[5][3], char playerName[2][100], int turn, int boatLength[5]){

    //NEED FEATURE FOR USER TO BE ABLE TO ESCAPE IF THEY GET STUCK

    char input, orientation,  duckedCell[3] = "  ";
    int hori, vert, newVert, newHori, valid;

    for(int i = 0; i < 5; i++){
        selectionStart:
        input = 0; // reset the input so while loop triggers again
        hori = 0; // reset every time NEED TO MAKE SURE IF USER PLACES BOAT AT ORIGIN WE FILTER FOR THAT
        vert = 0;
        newHori = hori;
        newVert = vert;
        strcpy(duckedCell, playerData[turn][vert][hori]); // copy the default location into the duckedCell
        strcpy(playerData[turn][vert][hori], "[]"); //user cursor

        while(input != 'q'){
            displayBoard(playerName, 0, turn, playerData); // show placement
            printf("\nEnter a direction with W/A/S/D, Q when finished\n");
            while(validateUserInput(&input) != 1){ // running validation check for user input
            printf("Invalid Input");
            }

            strcpy(playerData[turn][vert][hori], duckedCell); // put old cell back

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
                newVert = 0; //checking is user input is valid or not by forcing bounds
            if(newVert > 9)
                newVert = 9;
            if(newHori < 0)
                newHori = 0;
            if(newHori > 9)
                newHori = 9;

            if(strcmp(playerData[turn][newVert][newHori], "  ") != 0){ //checking the validity of the sqaure
                printf("This Cell is Taken, Try Again!\n");
                continue;
            }
            strcpy(playerData[turn][vert][hori], duckedCell); // erase old cursor
            vert = newVert;
            hori = newHori;
            strcpy(duckedCell, playerData[turn][vert][hori]);
            strcpy(playerData[turn][vert][hori], "[]"); //user cursor
        }
        printf("Place Boat %s (Length %d). Enter H for horizontal and V for vertical\n", boardPieces[i], boatLength[i]);
        while(validateUserInput(&orientation) != 1){ // running validation check for user input
            printf("Invalid Input");
        }

        valid = 0; // checking for validity

        while(valid == 0){
            valid = 1; // only changes if invalid
            for(int k = 1; k < boatLength[i]; k++){ // CHECKING BEFORE PLACING
                // If triggered on V and H then need escape sequence
                if(orientation == 'V' || orientation == 'v'){
                    if((vert + boatLength[i] - 1) >= 10){
                        valid = 0;
                        break;
                    }
                    if(strcmp(playerData[turn][vert + k][hori], "  ") != 0){
                        valid = 0;
                        break;
                    }
                }else if(orientation == 'H' || orientation == 'h'){
                    if((hori + boatLength[i] - 1) >= 10){
                        valid = 0;
                        break;
                    }
                    if(strcmp(playerData[turn][vert][hori + k], "  ") != 0){
                        valid = 0;
                        break;
                    }
                }else{ //invalid input and not invalid placement
                    valid = 0;
                    break;
                    }
                }

                if (!valid){
                    printf("Invalid Input Try Again or Type 'X' if Stuck\n"); //getting user input and trying again
                    scanf(" %c", &orientation);
                    if(orientation == 'X' || orientation == 'x'){ // resets values
                        strcpy(playerData[turn][vert][hori], duckedCell); //replace with old list item
                        goto selectionStart; // GOING BACK TO SELECTION
                    }
                }
        }
        for(int j = 0; j < boatLength[i]; j++){ // place boats now
            if(orientation == 'V' || orientation == 'v')
                strcpy(playerData[turn][vert + j][hori], boardPieces[i]); // place data

            else if (orientation == 'H' || orientation == 'h')
                strcpy(playerData[turn][vert][hori + j], boardPieces[i]); // place data
        }
        displayBoard(playerName, 0, turn, playerData); // display
    }
    //make function to pass everything as hotcodes
}
// END Handling User Input for Boat Placement Function



// Pause Function Prototype
void pause(char player[2][100]){
    char pauseIn;
    battleShipPause_ASCII();
    printf("\n\n\n\t\t\t   Enter anything except 'L' to Unpause \n\n");
    printf("If player %s would like to surrender, enter 'L'", player[2]);
    scanf(" %c", &pauseIn);
    if(pauseIn == 'L' || pauseIn == 'l'){}
        // INSERT WIN CONDITION WILL NEED TO USE POINTER TO ACCESS AND CHANGE
}
// END Pause Function Prototype




#endif // FUNCTIONS_H_INCLUDED
