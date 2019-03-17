#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printMap(int **);
void getInput(int **);
int checkInput(int**, int, int);
int **initializeMap();
int checkSum(int);
int checkforWin(int **);
void OpponentsTurn(int **map, int row, int col, int);
int checkforDraw(int **map);

int main(void){
    srand(time(NULL));
    
    int exitValue = 0;
    do{
        //creates the playing map
        int **map = initializeMap();
        
        //creates values that will exit the current game
        int winValue = 0;
        int drawValue = 0;
        do{
            //gets the users input, checks if it is valid
            getInput(map);
            //Checks if the game has been won
            //Checks if the game has reached a draw
            winValue = checkforWin(map);
            drawValue = checkforDraw(map);
            
            //If the game hasn't been one or reached a draw...
            //let the opponent make a move
            if(winValue == 0 && drawValue == 0){
                int Op_Attempts = 0;
                int Op_row = rand() % 3;
                int Op_col = rand() % 3;
                OpponentsTurn(map, Op_row, Op_col, 0);
                winValue = checkforWin(map);
            }
        }while(winValue == 0 && drawValue == 0);
        if(winValue == 0 && drawValue == 1)
		printf("It's a draw!\n");
        if(winValue == 1)
            printf("You Win!\n");
        if(winValue == 2)
            printf("Your Opponent has Won!\n");

        printf("Would you like to play again?: ");
        scanf("%d", &exitValue);
    }while(exitValue == 0);
    
    printf("Ending Program...\n");
    
    return 1;
}

int **initializeMap(){
    int**map = malloc(3 * sizeof(int*));
    for(int i = 0; i < 3; i++){
        *(map + i) = malloc(3 * sizeof(int));
    }
    
    for (int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            map[i][j] = 0;
        }
    }
    printMap(map);
    return map;
}

void printMap(int **map){
    printf("\n");
    
    for(int i = 0; i < 3; i++){
        int j = 0;
        printf("     |     |      \n");
        printf("  %d  |  %d  |  %d  \n", map[i][j], map[i][j + 1], map[i][j + 2] );
        printf("     |     |      \n");
        
        if(i == 0 || i == 1){
            printf("-----------------\n");
        }
    }
}

void getInput(int **map){
    int row;
    int col;
    do{
        printf("Row?: ");
        scanf("%d", &row);
        printf("Column?: ");
        scanf("%d", &col);
    }while(checkInput(map, row, col) == 0);
    printMap(map);
}

int checkInput(int **map, int row, int col){
    if(col > 2 || row > 2){
        printf("Your request is out of bounds, Please try again.\n");
        return 0;
    }
    
    if(map[row][col] == 1|| map[row][col] == 2){
        printf("Sorry, Space is taken. Try another!\n");
        return 0;
    }
    
    if(map[row][col] == 0){
        map[row][col] = 1;
        printf("Successfully Marked\n");
        return 1;
    }
    
    return 0;
}

int checkforWin(int **map){
    for(int i = 0; i < 3; i++){
        if(map[i][0] != 0 && map[i][0] == map[i][1] && map[i][1] == map[i][2]){
            return map[i][0];   
        }
    }
    for(int i = 0; i < 3; i++){
        if(map[0][i] != 0 && map[0][i] == map[1][i] && map[1][i] == map[2][i]){
            return map[0][i];   
        }
    }
    if(map[0][0] != 0 && map[0][0] == map[1][1] && map[1][1] == map[2][2])
        return map[0][0];
    if(map[0][2] != 0 && map[0][2] == map[1][1] && map[1][1] == map[2][0])
        return map[0][2];
        
    else
        return 0;
}

void OpponentsTurn(int **map, int row, int col, int attempt){
    printf("It is now the opponents turn...Attempting map[%d][%d]\n", row, col);
    while(attempt <= 10){
        if(map[row][col] == 1|| map[row][col] == 2){
            if(col < 2){
                OpponentsTurn(map, row, col += 1, attempt + 1);
                return;
            }

            if(row < 2){
                OpponentsTurn(map, row += 1, col, attempt + 1);
                return;
            }

            if(row == 2 && col == 2){
                OpponentsTurn(map, 0, 0, attempt + 1);
                return;
            }
        }

        if(map[row][col] == 0){
            map[row][col] = 2;
            printf("Opponent's Move Successfully Marked\n");
            printMap(map);
            return;
        }
    }
    printf("Attempts exceeded\n");
    return;   
}

int checkforDraw(int **map){
    int counter = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(map[i][j] == 0)
            counter++;
        }
    }
    printf("There are %d Zeros\n", counter);
    if(counter == 0)
        return 1;

    else
        return 0;
}
