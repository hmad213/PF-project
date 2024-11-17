#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>

//draws the menu and asks for user input
void draw_menu(){
    printf("  ______    ______   __    __   ______\n");  
    printf("/      \\  /      \\ /  |  /  | /      \\ \n");
    printf("/$$$$$$  |/$$$$$$  |$$ |  $$ |/$$$$$$  |\n");
    printf("$$____$$ |$$$  \\$$ |$$ |__$$ |$$ \\__$$ |\n");
    printf("/    $$/ $$$$  $$ |$$    $$ |$$    $$< \n");
    printf("/$$$$$$/  $$ $$ $$ |$$$$$$$$ | $$$$$$  |\n");
    printf("$$ |_____ $$ \\$$$$ |      $$ |$$ \\__$$ |\n");
    printf("$$       |$$   $$$/       $$ |$$    $$/ \n");
    printf("$$$$$$$$/  $$$$$$/        $$/  $$$$$$/\n");
}

// Gets a difficulty level from the user('E', 'M', 'H')
char select_difficulty(){
    draw_menu();
    char difficulty;
    printf("\nEnter a difficulty level(Easy: 'E', Medium: 'M', Hard: 'H'): ");
    scanf(" %c", &difficulty);
    while(difficulty != 'E' && difficulty != 'M' && difficulty != 'H'){
        system("cls");
        draw_menu();
        printf("\n Invalid difficulty. Try again(Easy: 'E', Medium: 'M', Hard: 'H'): ");
        scanf(" %c", &difficulty);
    }
    return difficulty;
}

//function to get size from difficulty('E', 'M' or 'H')
int get_size(char difficulty){
    int size;
    switch(difficulty){
        case 'E':
            size = 5;
            break;
        case 'M':
            size = 4;
            break;
        case 'H':
            size = 3;
    }
    return size;
}

//Takes a difficulty level ('E', 'M', 'H') and returns a grid of integers sized according to the difficulty
int** set_board(int size){
    int** board = (int**)malloc(size * sizeof(int*));
    for(int i = 0; i < size; i++){
        board[i] = (int*)malloc(size * sizeof(int));
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            board[i][j] = 0;
        }
    }
    return board;
}

//Takes a grid and prints the board
void draw_board(int** grid, int size){
    int i,j;
    for (i=0;i<size;i++){
    	printf("\n");
    	for(j=0;j<size;j++){
    		printf("  %d",grid[i][j]);
		}
	}
}
//Takes the input of the move of the user. Returns a char from 'W', 'A', 'S', 'D'
char take_input(){
    char move;
	int flag =0;
    printf("\nEnter your move (W = up, A = left, D = right, S= down, Q= quit): ");
    while(flag ==0 ){
    	scanf(" %c",&move);
    	if (move=='W' || move== 'A' || move== 'S' || move== 'D' || move== 'Q'){
    		flag =1;
		}
		else{
			printf("\nInvalid input try again (W = up, A = left, D = right, S= down, Q= quit): ");
		}
	}
	return move;
}

//Takes a move ('W', 'A', 'S', 'D') and returns 1 if a move is successful otherwise returns 0
int move(char move, int** grid, int size, int* score){
    int moved = 0;

    if (move == 'W') {
        for (int col = 0; col < size; col++) {
            int target = 0; 
            for (int row = 0; row < size; row++) {
                if (grid[row][col] != 0) {
                    if (target > 0 && grid[target - 1][col] == grid[row][col]) {
                        grid[target - 1][col] *= 2;
                        *score += grid[target - 1][col];
                        grid[row][col] = 0;
                        moved = 1;
                    } else {
                        if (row != target) {
                            grid[target][col] = grid[row][col];
                            grid[row][col] = 0;
                            moved = 1;
                        }
                        target++;
                    }
                }
            }
        }
    }
    
    else if (move == 'S') {
        for (int col = 0; col < size; col++) {
            int target = size - 1; 
            for (int row = size - 1; row >= 0; row--) {
                if (grid[row][col] != 0) {
                    if (target < size - 1 && grid[target + 1][col] == grid[row][col]) {
                        grid[target + 1][col] *= 2;
                        *score += grid[target + 1][col];
                        grid[row][col] = 0;
                        moved = 1;
                    } else {
                        if (row != target) {
                            grid[target][col] = grid[row][col];
                            grid[row][col] = 0;
                            moved = 1;
                        }
                        target--;
                    }
                }
            }
        }
    }

    else if (move == 'A') {
        for (int row = 0; row < size; row++) {
            int target = 0; 
            for (int col = 0; col < size; col++) {
                if (grid[row][col] != 0) {
                    if (target > 0 && grid[row][target - 1] == grid[row][col]) {
                        grid[row][target - 1] *= 2;
                        *score += grid[row][target - 1];
                        grid[row][col] = 0;
                        moved = 1;
                    } else {
                        if (col != target) {
                            grid[row][target] = grid[row][col];
                            grid[row][col] = 0;
                            moved = 1;
                        }
                        target++;
                    }
                }
            }
        }
    }

    else if (move == 'D') {
        for (int row = 0; row < size; row++) {
            int target = size - 1; 
            for (int col = size - 1; col >= 0; col--) {
                if (grid[row][col] != 0) {
                    if (target < size - 1 && grid[row][target + 1] == grid[row][col]) {
                        grid[row][target + 1] *= 2;
                        *score += grid[row][target + 1];
                        grid[row][col] = 0;
                        moved = 1;
                    } else {
                        if (col != target) {
                            grid[row][target] = grid[row][col];
                            grid[row][col] = 0;
                            moved = 1;
                        }
                        target--;
                    }
                }
            }
        }
    }

    return moved;
}

//Takes a grid and returns an array of the coordinates of all the blocks that are empty
int** get_empty_spaces(int** grid, int size){
    int** coordinates = NULL;
    int index = 0;

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if (grid[i][j] == 0){
                coordinates = (int**)realloc(coordinates, (index+1) * sizeof(int*));
                coordinates[index] = (int*)malloc(2 * sizeof(int));
                coordinates[index][0] = i;
                coordinates[index][1] = j;
                index++;
            }
        }
    }
    return coordinates;
}

//Takes a grid and generates a block of either 2 or 4 in a random empty space in the grid
void generate_random_block(int** grid, int size){
}

//Takes a grid and returns 1 if the game is over and 0 if not. This is ONLY for when the user has lost
int check_game_over(int** grid){
    
}

//Takes a grid and returns 1 if the user has won and 0 if not.
int check_win(int **grid, int size){
	int i,j,flag=0;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(grid[i][j] == 2048){
				return 1;
			}
		}
	}
	return 0;
}

//DEFINITION UNFINISHED. Takes a difficulty('E', 'M', 'H') and gets data from the appropriate text file
void get_high_scores(char difficulty){
    
}

//DEFINITION UNFINISHED. Takes a score, checks if it is a high score, and saves it appropriately 
void save_high_scores(){
    
}

//Provides the functionality of the game. Game should refresh after every move. Check select_difficulty for reference
void game_process(){
    
}

int main(void){
    char difficulty = select_difficulty();
    int size = get_size(difficulty);
    int** grid = set_board(size);
    int flag = 1;
    int* score = 0;
    grid[0][1] = 2;
    grid[1][0] = 2;
    while(flag = 1){
        draw_board(grid, size);
        char input = take_input();
        int successful = move(input, grid, size, score);
    }
    
    
    
    // Don't touch
    for(int i = 0; i < size; i++)
        free(grid[i]);
    free(grid);
}