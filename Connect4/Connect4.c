#include <stdio.h>
#include <stdbool.h>

#define ROWS 6
#define COLS 6
#define EMPTY '-'
#define RED 'R'
#define YELLOW 'Y'

//create empty board
void createBoard(char gameBoard[][COLS]){
    for (int j = 0; j < ROWS; j++){
        for (int i = 0; i < COLS; i++){
            gameBoard[j][i] = EMPTY;
        }
    }
}

//print board after user input
void printBoard(char gameBoard[][COLS]) {
    for (int j = 0; j < ROWS; j++){
        for (int i = 0; i < COLS; i++){
            printf("%c", gameBoard[j][i]);
        }
        printf("\n");
    }
}

//prompt user on turn for column number
int getInput(char gameBoard[][COLS], char turn){
    int bounds;

    do {
    if (turn == 'Y'){
    printf("Yellow, please enter a valid column number (0-5): ");
    } else if (turn == 'R'){
    printf("Red, please enter a valid column number (0-5): ");
    }
    scanf("%d", &bounds);
    } while (bounds < 0 || bounds >= 6 || (gameBoard[0][bounds] != EMPTY));

    return bounds;
}

//inserts piece of player of turn into board
void insertPiece(char gameBoard[][COLS], int columnEntered, char turn){
    
    for (int i = ROWS; i > 0; i--){
        if (gameBoard[i-1][columnEntered] == EMPTY){
            gameBoard[i-1][columnEntered] = turn;
            break;
        }
    }
}

//change turn to other player
void switchTurn(char* turn){
    if(*turn == RED){
        *turn = YELLOW;
    } else{
        *turn = RED;
    }
}

//check if there are four same pieces in each direction
bool checkOneDirection(char gameBoard[][COLS], int row, int col, int rowDir, int colDir){
    bool check = false;

    //top right
    if(rowDir == 1 && colDir == 1){
        for (int i = 0; i < 4; i++){
            if((gameBoard[row][col] == gameBoard[row-i][col+i]) && gameBoard[row][col] != '-'){
                check = true;
            } else {
                check = false;
                break;
            }
        }
    //bottom left    
    } else if (rowDir == -1 && colDir == -1){
        for (int i = 0; i < 4; i++){
            if ((gameBoard[row][col] == gameBoard[row+i][col-i]) && gameBoard[row][col] != '-'){
                check = true;
            } else {
                check = false;
                break;
            }
        }
    //top left
    } else if (rowDir == 1 && colDir == -1){
        for (int i = 0; i < 4; i++){
            if ((gameBoard[row][col] == gameBoard[row-i][col-i]) && gameBoard[row][col] != '-'){
                check = true;
            } else {
                check = false;
                break;
            }
        }
    //bottom right
    } else if (rowDir == -1 && colDir == 1){
        for (int i = 0; i < 4; i++){
            if ((gameBoard[row][col] == gameBoard[row+i][col+i]) && gameBoard[row][col] != '-'){
                check = true;
            } else {
                check = false;
                break;
            }
        }
    //right
    } else if (rowDir == 0 && colDir == 1){
        for (int i = 0; i < 4; i++){
            if ((gameBoard[row][col] == gameBoard[row][col+i]) && gameBoard[row][col] != '-'){
                check = true;
            } else {
                check = false;
                break;
            }
        }
    //left
    } else if (rowDir == 0 && colDir == -1){
        for (int i = 0; i < 4; i++){
            if ((gameBoard[row][col] == gameBoard[row][col-i]) && gameBoard[row][col] != '-'){
                check = true;
            } else {
                check = false;
                break;
            }
        }
    //up
    } else if (rowDir == 1 && colDir == 0){
        for (int i = 0; i < 4; i++){
            if ((gameBoard[row][col] == gameBoard[row-i][col]) && gameBoard[row][col] != '-'){
                check = true;
            } else {
                check = false;
                break;
            }
        }
    //down
    } else if (rowDir == -1 && colDir == 0){
        for (int i = 0; i < 4; i++){
            if ((gameBoard[row][col] == gameBoard[row+i][col]) && gameBoard[row][col] != '-'){
                check = true;
            } else {
                check = false;
                break;
            }
        }
    }

    return check;
}

//check if there is a winner (four pieces in a row)
bool checkWinner(char gameBoard[][COLS]){
    bool final = false;
    
    for (int i = 0; i < ROWS; i++){
            for (int j = 0; j < COLS; j++){
            for (int k = -1; k < 2; k++){
                for (int m = -1; m < 2; m++){
                    final = checkOneDirection(gameBoard, i, j, k, m);
                    if (final){
                        return final;
                    }
                }
            }
        }
    }
    return final;
}


int main(void){
    //initialize gameboard
    char gameBoard[ROWS][COLS];
    char turn = RED;
    bool full = false;
    createBoard(gameBoard);
    
    //keep running until winner
    while (true){
        printBoard(gameBoard);
        insertPiece(gameBoard, getInput(gameBoard, turn), turn);
        if (checkWinner(gameBoard)){
            break;
        }
        switchTurn(&turn);

    
    //check if it is a tie
        for (int i = 0; i < COLS; i++){
            if (gameBoard[0][i] != EMPTY){
                    full = true;
            } else {
                full = false;
            }
        }
        if (full){
            turn = EMPTY;
            break;
        }
    }

    //print winner
    if (turn == RED){
        printf("Red wins!\n");
    } else if (turn == YELLOW){
        printf("Yellow wins!\n");
    } else {
        printf("It's a tie\n");
    }
    //print final result
    printf("Final board: \n");
    printBoard(gameBoard);
}
