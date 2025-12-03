//==========================================
// Name: BattleShipCPE223
// Author: Wyatt Bowman
// Date: 12/2/25
// Version: V0.9
// Description: battleships- the game
// Changes: Adding Attacking
//==========================================

#include <stdio.h>
#include <string.h> // Required to use strings
#include <stdlib.h> // Required for system()
#include <stdbool.h>
#include "functions.h"


int main(){
    //Start Variables
    int userX, userY, rotate, turn = 0, booleanTurn = 0, value = 1;
    int boatLength[5] = {5, 4, 3, 3, 2};
    int shipValueType[5]={10,8,6,4,2};
    int playerData[2][10][10]={0}; // player, row, column

    char playerName[2][100]; // make smaller in future
    char shipValueAbrv[14][5] = {" ~~ "," 00 "," AC ","XACX"," BA ","XBAX"," SU ","XSUX"," CR ","XCRX"," DE ","XDEX"," [] ","Sunk"};
    char mainScreenOption = 0;
    char oldMainScreenOption = 0;

    char ships[5][20] = {"Carrier", "Battleship", "Submarine", "Cruiser", "Destroyer"};

    bool screenShake = false; // FOR GAME NEEDS TO BE DYNAMIC
    //End Variables

    while(!(mainScreenOption == 'q' || mainScreenOption == 'Q')){ // change to when user enters new line then quits
        battleShipCover_ASCII(); // ASCII ART from void function
        startScreen(value);
        while(!validateUserInput(&mainScreenOption)){ // running validation check for user input
            printf("Invalid Input");
        }

        if(mainScreenOption == 'w' || mainScreenOption == 'W')
            value--;
                if(value < 1)
                    value = 3;
        else if (mainScreenOption == 's' || mainScreenOption == 'S')
            value++;
                if(value > 3)
                    value = 1;
        system("cls"); // clears terminal
    }

    switch(value){

        case 1: // PLAY GAME

            for(int playerNumber = 0; playerNumber < 2; playerNumber++){ // getting the usernames of each player
                printf("\t\t\n\nWhat is the name of Player %d?:\t\n\n", playerNumber + 1);
                fgets(playerName[playerNumber], sizeof(playerName[playerNumber]), stdin);
                int length = strlen(playerName[playerNumber]); // bad practice fix later
                playerName[playerNumber][length - 1] = '\0'; // making sure the last real character isn't a newline
            }

                //Player One Placement
                getUserBoatPlacement(playerData, playerName, booleanTurn, boatLength, shipValueType, shipValueAbrv, ships);
                //Transition
                transistion(turn + 1);
                //Player Two Placement
                getUserBoatPlacement(playerData, playerName, booleanTurn + 1, boatLength, shipValueType, shipValueAbrv, ships);




            while(1){ // need win condition

                displayBoard(playerName, screenShake, booleanTurn, playerData, shipValueAbrv); // just testing output

                if(screenShake){
                    for(int shakeAmount = 0; shakeAmount < 4; shakeAmount++){
                        displayBoard(playerName, (!(shakeAmount % 2)), booleanTurn, playerData, shipValueAbrv);
                        _sleep(500); //sleep 100ms from windows.h
                    }
                }
                attackSmack(booleanTurn, playerData, playerName, shipValueAbrv);
                turn++;
                booleanTurn = turn % 2;
                transistion(booleanTurn);
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
