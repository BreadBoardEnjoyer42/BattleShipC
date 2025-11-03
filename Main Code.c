//==========================================
// Name: BattleShipCPE223
// Author: Wyatt Bowman
// Date: 11/1/25
// Version: V0.2
// Description:
// Changes: 1. Fixed coordinate system it was reversed. 2. Added vertical boats, still not overlapping protection
//==========================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Required to use strings
#include <stdlib.h> // Required for system()

int setBoats(int, int, int, int);
void showBoard(); // declaring function that shows board

int BattleArray[11][11] = {0}; // declaring array, indexing starts with one


int main()
{
    int userX, userY;
    char Ships[5][20] = {"Carrier", "Battleship", "Submarine", "Cruiser", "Destroyer"}; // names and such
    int rotate;


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

    return 0;
}

int setBoats(int xCoord, int yCoord, int boatIndex, int orientation){ //placing boats

    int length[5] = {5, 4, 3, 3, 2}; // lengths of each piece

    if(orientation == 1){
        for (int iVert = 0; iVert < length[boatIndex]; iVert++) {
            BattleArray[yCoord + iVert][xCoord] = 1; // placing boats in array with size
        }
    }else if(orientation == 0){
        for (int iHor = 0; iHor < length[boatIndex]; iHor++) {
            BattleArray[yCoord][xCoord + iHor] = 1; // placing boats in array with size, not placing horizontally fix
        }
    }
    return 1;
}


void showBoard(){ // shows board, makes sense ig
    system("cls"); // clears terminal
for(int i = 0; i <= 10; i++){
        printf("\n\n");
        for(int j = 0; j <= 10; j++){
             printf("%d  ", BattleArray[i][j]);
        }
    }
}


