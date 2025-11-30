#include <stdio.h>
#include <string.h> // Required to use strings
#include <stdlib.h> // Required for system()
#include <stdbool.h>
// say I start with some matrix BattleArray
    int ActualArray[2][10][10]={0};
    int BattleArray[2][10][10]={0};
    char ships[5][20] = {"Carrier","Battleship","Submarine","Cruiser","Destroyer"};
    char shipValueAbrv[14][5] = {" ~~ "," OO "," CY ","XCYX"," BA ","XBAX"," SU ","XSUX"," CR ","XCRX"," DE ","XDEX","[]","Sunk"};
    int shipValueType[5]={2,4,6,8,10};
    int shipSize[5]= {2,3,3,4,5};

    void gameSetUp();
    void readyPlayer(int player);
    void attackSmack(int player,bool warnDoubleAttack);
    void showIntegerBoatBoard(int player);
    void printDesignBoard(int player);
    void printPlayerBattleBoardRow(int player,int row);
    void printingPlayerBoards(int player,bool warnDoubleAttack);
    void printPlayerBoardRow(int player,int row);
    void printPlayerFogBoardRow(int player,int row);

int main(){

    gameSetUp();
    //START OF GAME
    bool notAllShipSunk=true;
    int curPlayer=0;
    bool warnDoubleAttack=false;
    while(notAllShipSunk){
        //------Ready Player?---------
        readyPlayer(curPlayer);
        //-------Print Boards---------
        printingPlayerBoards(curPlayer,warnDoubleAttack);
        //----------Attack------------
        attackSmack(curPlayer,warnDoubleAttack);
        //-------Print Boards---------
        printingPlayerBoards(curPlayer,warnDoubleAttack);
        curPlayer=!curPlayer;
    }
    return 0;
}

void gameSetUp(){

    bool warnForMovement=false;
    bool boatPlacementIncomplete=true;
    bool warnForValidMovement=false;
    bool warnBoatOverlap=false;
    bool rotationType;
    char movement[100];
    int xcoord;
    int ycoord;

    for(int player=0;player<2;player++){
        for(int i=0;i<5;i++){
            for(int j=0;j<shipSize[i];j++){
                BattleArray[player][j][0]=shipValueType[i];
            }
            rotationType=true;
            while(boatPlacementIncomplete){
                printDesignBoard(player);
                printf("\nPlease place your %s.\n",ships[i]);
                if (warnForMovement){
                    printf("The boat can't move any farther in that direction...\n");
                    warnForMovement=false;
                 }
                if (warnForValidMovement) {
                    printf("Please put in a valid movement.\n");
                    warnForValidMovement=false;
                }
                if (warnBoatOverlap){
                    printf("The boat placement overlaps with an already placed boat.\n");
                    warnBoatOverlap=false;
                }
                printf("Movement Codes: \n-w to move up \n-s to move down \n-a to move left \n-d to move right \n-r to rotate the boat \nWhen you've decided where to place the boat use f to lock in the boat.\n");
                fgets(movement, sizeof(movement), stdin);// Need to make adjustments for adapting to user input, currently being lazy by making
                // a huge buffer and calling it a day, but if the user put in an input over 100 characters, there would be excess into the buffer which would reach into the next input cycle
                for(int y=0;y<10;y++){
                    for(int x=0;x<10;x++){
                        if (BattleArray[player][y][x]==shipValueType[i]){
                            if (rotationType){
                                xcoord=x;
                                ycoord=y-shipSize[i]+1;
                            }
                            else{
                                xcoord=x-shipSize[i]+1;
                                ycoord=y;
                            }
                        }
                    }
                }
                if (movement[0]=='w'){
                    for(int x=0;x<10;x++){
                        if(BattleArray[player][0][x]==shipValueType[i]){
                            warnForMovement=true;
                        }
                    }
                    if(warnForMovement){
                            continue;
                    }
                    if (rotationType){
                        for(int u=(ycoord-1);u<(ycoord+shipSize[i]-1);u++){
                            BattleArray[player][u][xcoord]=shipValueType[i];
                        }
                        BattleArray[player][ycoord+shipSize[i]-1][xcoord]=ActualArray[player][ycoord+shipSize[i]-1][xcoord];
                    }
                    else{
                        for(int u=xcoord;u<(xcoord+shipSize[i]);u++){
                            BattleArray[player][ycoord-1][u]=shipValueType[i];
                            BattleArray[player][ycoord][u]=ActualArray[player][ycoord][u];
                        }
                    }
                }
                else if (movement[0]=='s'){
                    for(int x=0;x<10;x++){
                        if(BattleArray[player][9][x]==shipValueType[i]){
                            warnForMovement=true;
                        }
                    }
                    if(warnForMovement){
                        continue;
                    }
                    if (rotationType){
                        for(int u=(ycoord+1);u<(ycoord+shipSize[i]+1);u++){
                            BattleArray[player][u][xcoord]=shipValueType[i];
                        }
                        BattleArray[player][ycoord][xcoord]=ActualArray[player][ycoord][xcoord];
                    }
                    else{
                        for(int u=xcoord;u<(xcoord+shipSize[i]);u++){
                            BattleArray[player][ycoord+1][u]=shipValueType[i];
                            BattleArray[player][ycoord][u]=ActualArray[player][ycoord][u];
                        }
                    }
                }
                else if (movement[0]=='a'){
                    for(int y=0;y<10;y++){
                        if(BattleArray[player][y][0]==shipValueType[i]){
                            warnForMovement=true;
                        }
                    }
                    if(warnForMovement){
                        continue;
                        }
                    if (rotationType){
                        for(int u=ycoord;u<(ycoord+shipSize[i]);u++){
                            BattleArray[player][u][xcoord-1]=shipValueType[i];
                            BattleArray[player][u][xcoord]=ActualArray[player][u][xcoord];
                        }
                    }
                    else{
                        for(int u=(xcoord-1);u<(xcoord+shipSize[i]-1);u++){
                            BattleArray[player][ycoord][u]=shipValueType[i];
                        }
                        BattleArray[player][ycoord][xcoord+shipSize[i]-1]=ActualArray[player][ycoord][xcoord+shipSize[i]-1];
                    }
                }
                else if (movement[0]=='d'){
                    for(int y=0;y<10;y++){
                        if(BattleArray[player][y][9]==shipValueType[i]){
                            warnForMovement=true;
                        }
                    }
                    if(warnForMovement){
                        continue;
                        }
                    if (rotationType){
                        for(int u=ycoord;u<(ycoord+shipSize[i]);u++){
                            BattleArray[player][u][xcoord+1]=shipValueType[i];
                            BattleArray[player][u][xcoord]=ActualArray[player][u][xcoord];
                        }
                    }
                    else{
                        for(int u=(xcoord+1);u<(xcoord+shipSize[i]+1);u++){
                            BattleArray[player][ycoord][u]=shipValueType[i];
                        }
                        BattleArray[player][ycoord][xcoord]=ActualArray[player][ycoord][xcoord];
                    }
                }
                else if (movement[0]=='r'){
                    if(rotationType){
                        for(int u=ycoord;u<(ycoord+shipSize[i]);u++){
                            BattleArray[player][u][xcoord]=ActualArray[player][u][xcoord];
                        }
                            if(xcoord<5){
                                for(int p=xcoord;p<(xcoord+shipSize[i]);p++){
                                    BattleArray[player][ycoord][p]=shipValueType[i];
                                }
                            }
                            else{
                                for(int p=(xcoord-shipSize[i]+1);p<(xcoord+1);p++){
                                    BattleArray[player][ycoord][p]=shipValueType[i];
                                }
                            }
                        rotationType=false;
                    }
                    else{
                        for(int u=xcoord;u<(xcoord+shipSize[i]);u++){
                            BattleArray[player][ycoord][u]=ActualArray[player][ycoord][u];
                        }
                            if(ycoord<5){
                                for(int p=ycoord;p<(ycoord+shipSize[i]);p++){
                                    BattleArray[player][p][xcoord]=shipValueType[i];
                                }
                            }
                            else{
                                for(int p=(ycoord-shipSize[i]+1);p<(ycoord+1);p++){
                                    BattleArray[player][p][xcoord]=shipValueType[i];
                                }
                            }
                        rotationType=true;
                    }
                }
                else if (movement[0]=='f'){
                    if (rotationType){
                        for(int p=(ycoord);p<(ycoord+shipSize[i]);p++){
                            if(ActualArray[player][p][xcoord]!=0){
                                warnBoatOverlap=true;
                            }
                        }
                        if(warnBoatOverlap){
                            continue;
                        }
                        for(int u=ycoord;u<(ycoord+shipSize[i]);u++){
                        ActualArray[player][u][xcoord]=BattleArray[player][u][xcoord];
                        }
                    }
                    else{
                        for(int p=(xcoord);p<(xcoord+shipSize[i]);p++){
                            if(ActualArray[player][ycoord][p]!=0){
                                warnBoatOverlap=true;
                            }
                        }
                        if(warnBoatOverlap){
                            continue;
                        }
                        for(int u=xcoord;u<(xcoord+shipSize[i]);u++){
                        ActualArray[player][ycoord][u]=BattleArray[player][ycoord][u];
                        }
                    }
                    boatPlacementIncomplete=false;
                }
                else{
                    warnForValidMovement=true;
                }
            }
            boatPlacementIncomplete=true;
        }
    }
}

void readyPlayer(int player){
    char readyConfirmation[100];
    readyConfirmation[0]='w';
    while(readyConfirmation[0]!='y'){
        printf("Ready Player %d? Type y to confirm.",(player+1));
        fgets(readyConfirmation, sizeof(readyConfirmation), stdin);
    }
}

void showIntegerBoatBoard(int player){
    printf("\nPlayer %d's Board of Boats\n",player);
    for(int j = 0; j < 10; j++){
        printf("\n\n");
        for(int i = 0; i < 10; i++){
             printf("%d", ActualArray[player][j][i]);
        }
    }
}

void printDesignBoard(int player){
    for(int i=0;i<10;i++){
    for (int j=0;j<10;j++){
        printf("+----");
    }
    printf("+\n");
    printPlayerBattleBoardRow(player,i);
    printf("\n");
    }
    for (int j=0;j<10;j++){
    printf("+----");
    }
    printf("+");
}

void printPlayerBattleBoardRow(int player,int row){
    for (int col=0;col<10;col++){
        printf("|");
        printf(shipValueAbrv[BattleArray[player][row][col]]);
    }
    printf("|");
}

void printingPlayerBoards(int player,bool warnDoubleAttack){
    for(int i=0;i<10;i++){
        for (int j=0;j<10;j++){
            printf("+----");
        }
        printf("+\t");
        for (int j=0;j<10;j++){
            printf("+----");
        }
        printf("+\n");
        printPlayerBoardRow(player,i);
        printf("\t");
        printPlayerFogBoardRow((!player),i);
        printf("\n");
    }
    for (int j=0;j<10;j++){
        printf("+----");
    }
    printf("+\t");
    for (int j=0;j<10;j++){
        printf("+----");
    }
    printf("+\n");

    if(warnDoubleAttack){
        printf("You can't attack the same location more than once.");
        warnDoubleAttack=false;
    }
}

void printPlayerBoardRow(int player,int row){
    for (int col=0;col<10;col++){
        printf("|");
        printf(shipValueAbrv[ActualArray[player][row][col]]);
    }
    printf("|");
}

void printPlayerFogBoardRow(int player,int row){
    for (int col=0;col<10;col++){
        printf("|");
        if (ActualArray[player][row][col]==1){
            printf("Miss");
        }
        else if ((ActualArray[player][row][col])%2){
            printf(" XX ");
        }
        else{
            printf(" ~~ ");
        }
    }
    printf("|");
}


void attackSmack(int player, bool warnDoubleAttack){
    int attackRow;
    int attackCol;
    printf("What row do you want to attack?");
    scanf("%d",&attackRow);
    printf("What column do you want to attack?");
    scanf("%d",&attackCol);
    if(!((ActualArray[(!player)][attackRow][attackCol])%2))
        ActualArray[(!player)][attackRow][attackCol]+=1;
    else{
        warnDoubleAttack=true;
    }
}
