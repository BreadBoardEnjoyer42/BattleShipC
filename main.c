//==========================================
// Name: BattleShipCPE223
// Author: Wyatt Bowman
// Date: 12/6/25
// Version: V0.14
// Description: Win Condition, Scoring, finalized visuals, AND added surrender in pause menu
// Changes: fixed win condition, score is now displayed after every turn, and now you can see if where you hit is a miss or hit
//
//==========================================

#include <stdio.h>
#include <string.h> // Required to use strings
#include <stdlib.h> // Required for system()
#include <stdbool.h>
#include "functions.h"
int size;
int playerPoints[2] = {0};
int CHECK[2][20][20] = {0};


int main(){
    //Start Variables
    int userX, userY, rotate, turn = 0, booleanTurn = 0, value = 1;
    int boatLength[5] = {5, 4, 3, 3, 2};
    int shipValueType[5]={2,4,6,8,10};
    int playerData[2][20][20]={0}; // player, row, column

    char playerName[2][100]; // make smaller in future
    char shipValueAbrv[14][5] = {" ~~ ","Miss"," AC ","XACX"," BA ","XBAX"," SU ","XSUX"," CR ","XCRX"," DE ","XDEX"," [] ","Sunk"};
    char mainScreenOption = 0;
    char oldMainScreenOption = 0;

    char ships[5][20] = {"Carrier", "Battleship", "Submarine", "Cruiser", "Destroyer"};

    bool screenShake = false; // FOR GAME NEEDS TO BE DYNAMIC
    bool airStrikeMode = false;
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
            getSize(&size);
            //Player One Placement
            getMode(&airStrikeMode);
            // does the user want to play airstrike mode?
            getUserBoatPlacement(playerData, playerName, booleanTurn, boatLength, shipValueType, shipValueAbrv, ships);
            //Transition
            transistion(turn + 1);
            //Player Two Placement
            getUserBoatPlacement(playerData, playerName, booleanTurn + 1, boatLength, shipValueType, shipValueAbrv, ships);
            //Transition
            transistion(turn);



            while(1){ // need win condition

                if(screenShake == true){
                    for(int shakeAmount = 0; shakeAmount < 6; shakeAmount++){
                        displayBoard(playerName, (!(shakeAmount % 2)), booleanTurn, playerData, shipValueAbrv);
                        _sleep(300); //sleep 100ms from windows.h
                    }
                screenShake = false;
                }

                displayBoard(playerName, 0, booleanTurn, playerData, shipValueAbrv); // just testing output
                //Display The board
                attackSmack(booleanTurn, playerData, playerName, shipValueAbrv, &screenShake, airStrikeMode);
                //ATTACKKKKKKKKKKKKK
                printf("\n\t\t Points: %d", playerPoints[booleanTurn]);
                winCondition(playerData, booleanTurn);
                if(playerPoints[booleanTurn] >= 11200){
                    winScreen_ASCII(booleanTurn);
                    return 0;
                }
                //test win condition
                turn++;
                //next persons turn
                booleanTurn = turn % 2;
                // for switching back and forth
                transistion(booleanTurn);
                //in between slide
            }
        break;
        case 2: // HELP OPTION
            printf("\n\nVisit \"https://www.wikihow.com/Play-Battleship\" for more information\n\n");
        break;
        case 3: // CREDITS
            printf("\n\nDeveloped by Wyatt Bowman and Kieran Cavanagh\n\n");
            titleScreen();
        break;
        default:
            printf("Invalid Input, Try again");
    }


    return 0;

}

// END MAIN
