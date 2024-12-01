#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

//draws the menu and asks for user input
void drawLogo(){
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

// Gets a valid difficulty level from the user('E', 'M', 'H') and draws the menu
char drawMenuAndSelectDifficulty(){
    drawLogo();
    char difficulty;
    printf("\nEnter a difficulty level(Easy: 'E', Medium: 'M', Hard: 'H', Quit: 'Q'): ");
    scanf(" %c", &difficulty);
    difficulty = toupper(difficulty);
    while(difficulty != 'E' && difficulty != 'M' && difficulty != 'H' && difficulty != 'Q'){
        system("cls");
        drawLogo();
        printf("\n Invalid difficulty. Try again(Easy: 'E', Medium: 'M', Hard: 'H', Quit: 'Q'): ");
        scanf(" %c", &difficulty);
        difficulty = toupper(difficulty);
    }
    return difficulty;
}

//function to get size from difficulty('E', 'M' or 'H')
int getSize(char difficulty){
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
int** setBoard(int size){
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
void drawBoard(int** grid, int size, int score){
    int i , j, l = 0, ls = 1, number, gap = 0, space, g;
    system("cls");
    printf("\n\n");
    for(i = 0; i < size; i++){
    	for(j = 0; j < size; j++){
    		if (grid[i][j] > l){
    			l = grid[i][j];
			}
		}
	}
    while(l !=0){
    	l = l/10;
    	ls++;
	}
    printf("                Score: %d\n", score);
    printf("                ");
    for(i = 0; i < ls * size + 2; i++){
        printf("-");
    }
    for(i = 0; i < size; i++){
    	printf("\n                |");
    	for(j = 0; j < size; j++){
            if(grid[i][j] != 0){
                printf("%d",grid[i][j]);
            }
    		else{
                printf(".");
            }
            number = grid[i][j];
            gap = 0;
            while(number > 0){
            	gap++;
            	number = number/10;
			}
			if (grid[i][j] == 0){
				gap = 1;
			}
            space = ls - gap;
			for(g = 0; g < space; g++){
           		printf(" ");
			}
			
		}
        printf("|");
	}
    printf("\n");
    printf("                ");
    for(i = 0; i < ls * size + 2; i++){
        printf("-");
    }
}
//Takes valid input of the move of the user and draws the game. Returns a char from 'W', 'A', 'S', 'D'
char drawGameAndTakeInput(int** grid, int size, int score){
    char move;
	int flag = 0;
    drawBoard(grid, size, score);
    printf("\nEnter your move (W = up, A = left, D = right, S = down, Q = quit): ");
    while(flag == 0){
    	move = getch();
        move = toupper(move);
    	if (move =='W' || move == 'A' || move == 'S' || move == 'D' || move == 'Q'){
    		flag = 1;
		}
		else{
            drawBoard(grid, size, score);
			printf("\nInvalid input try again (W = up, A = left, D = right, S = down): ");
		}
	}
	return move;
}

//Takes a move ('W', 'A', 'S', 'D') and returns 1 if a move is successful otherwise returns 0
int move(char move, int** grid, int size, int* scorePtr){
    int moved = 0;
    if (move == 'W') {
        for (int col =0; col < size; col++) {
            int target = 0; 
            int flag = 0;
            for (int row = 0; row < size; row++) {
                if (grid[row][col] != 0) {
                    if (target >0 && grid[target -1][col] == grid[row][col]) {
                        if (flag == 0){
                            grid[target - 1][col] *= 2;
                            *scorePtr = *scorePtr + grid[target - 1][col];
                            grid[row][col] = 0;
                            moved = 1;
                            flag = 1;
                        }
                        else{
                            flag = 0;
                            grid[target][col] = grid[row][col];
                            grid[row][col] = 0;
                            target++;
                        }
                    } else {
                        if (row!= target) {
                            grid[target][col] = grid[row][col];
                            grid[row][col] = 0;
                            moved = 1;
                            flag = 0;
                        }
                        target++;
                    }
                }
            }
        }
    }
    
    else if (move == 'S') {
        for (int col= 0; col < size; col++) {
            int target = size - 1; 
            int flag = 0;
            for (int row = size - 1; row >= 0; row--) {
                if (grid[row][col] != 0) {
                    if (target < size - 1 && grid[target + 1][col] == grid[row][col]) {
                        if(flag == 0){
                            grid[target + 1][col] *= 2;
                            *scorePtr += grid[target + 1][col];
                            grid[row][col] = 0;
                            moved = 1;
                            flag = 1;
                        }
                        else{
                            flag = 0;
                            grid[target][col] = grid[row][col];
                            grid[row][col] = 0;
                            target--;
                        }
                    } else {
                        if (row!= target) {
                            grid[target][col] = grid[row][col];
                            grid[row][col] = 0;
                            moved = 1;
                            flag = 0;
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
            int flag = 0;
            for (int col = 0; col < size; col++) {
                if (grid[row][col] != 0) {
                    if (target > 0 && grid[row][target - 1] == grid[row][col]) {
                        if (flag == 0){
                            grid[row][target - 1] *= 2;
                            *scorePtr += grid[row][target - 1];
                            grid[row][col] = 0;
                            moved = 1;
                            flag = 1;
                        }
                        else{
                            flag = 0;
                            grid[row][target] = grid[row][col];
                            grid[row][col] = 0;
                            target++;
                        }
                    } else {
                        if (col != target) {
                            grid[row][target] = grid[row][col];
                            grid[row][col] = 0;
                            moved = 1;
                            flag = 0;
                        }
                        target++;
                    }
                }
            }
        }
    }

    else if (move == 'D') {
        for (int row= 0; row < size; row++) {
            int target = size - 1; 
            int flag = 0;
            for (int col = size - 1; col >= 0; col--) {
                if (grid[row][col] != 0) {
                    if (target < size - 1 && grid[row][target + 1] == grid[row][col]) {
                        if (flag == 0){
                            grid[row][target + 1] *= 2;
                            *scorePtr += grid[row][target + 1];
                            grid[row][col] = 0;
                            moved = 1;
                            flag = 1;
                        }
                        else{
                            flag = 0;
                            grid[row][target] = grid[row][col];
                            grid[row][col] = 0;
                            target--;
                        }
                    } else {
                        if (col!= target) {
                            grid[row][target] = grid[row][col];
                            grid[row][col] = 0;
                            moved = 1;
                            flag = 0;
                        }
                        target--;
                    }
                }
            }
        }
    }

    return moved;
}


//Takes a grid and returns number of empty spaces
int getEmptyNumber(int** grid, int size){
    int total = 0;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if (grid[i][j] == 0){
                total++;
            }
        }
    }
    return total;
}

//Takes a grid and returns an array of the coordinates of all the blocks that are empty
int** getEmptySpaces(int** grid, int size){
    int total = getEmptyNumber(grid, size);
    int** coordinates = (int**)malloc(total * sizeof(int*));
    for(int i = 0; i < total; i++){
        coordinates[i] = (int*)malloc(2 * sizeof(int));
    }
    int index = 0;

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if (grid[i][j] == 0){
                coordinates[index][0] = i;
                coordinates[index][1] = j;
                index++;
            }
        }
    }
    return coordinates;
}

//Takes a grid and generates a block of either 2 or 4 in a random empty space in the grid
void generateRandomBlock(int** grid, int size){
    int** coordinates = getEmptySpaces(grid, size);
    int total = getEmptyNumber(grid, size);
    int randIndex = rand() % total;
    int randNumber = (rand() % 10) + 1;
    if(randNumber < 9){
        grid[coordinates[randIndex][0]][coordinates[randIndex][1]] = 2;
    }
    else{
        grid[coordinates[randIndex][0]][coordinates[randIndex][1]] = 4;
    }

    for(int i = 0; i < total; i++){
        free(coordinates[i]);
    }
    free(coordinates);
}

//Takes a grid and returns 1 if the game is over and 0 if not. This is ONLY for when the user has lost
int checkGameOver(int** grid, int size) {
    int i, j;
    if (getEmptyNumber(grid, size) != 0) {
        return 0;
    }
    for (i = 0; i < size; i++) {
        for (j = 0; j < size - 1; j++) {
            if (grid[i][j] == grid[i][j + 1]) {
                return 0;
            }
        }
    }
    for (j = 0; j < size; j++) {
        for (i = 0; i < size - 1; i++) {
            if (grid[i][j] == grid[i + 1][j]) {
                return 0;
            }
        }
    }
    return 1;
}


//Takes a grid and returns 1 if the user has won and 0 if not.
int checkWin(int **grid, int size){
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

//Takes a filename, gets data from it and stores it in an integer array
int* getHighScores(char fileName[]){
    char line[10];
    int i = 0;
    int* scores = (int*)malloc(5 * sizeof(int));
    if(scores == NULL){
        printf("Could not allocate memory\n");
        return NULL;
    }

    FILE* filePtr = fopen(fileName, "r");
    if (filePtr == NULL) {
        printf("Could not read file");
        return NULL;
    }

    while(i < 5 && fgets(line, sizeof(line), filePtr) != NULL){
        sscanf(line, "%d\n", &scores[i]);
        i++;
    }

    fclose(filePtr);
    return scores;
}

//Takes a score and a sorted list of scores. Check if the score is greater than any score on the list and place it accordingly
int saveHighScores(int* scores, int score){
    int index = -1;
    for(int i = 0; i < 5; i++){
        if(score > scores[i]){
            if(i != 0){
                scores[i - 1] = scores[i];       
            }
            scores[i] = score;
            index = i;
        }
        else{
            return index;
        }
    }
}

//Takes the User score and sorted list of scores and displays them.
void displayHighScores(int* scores, int score){
    printf("Your Score: %d\n", score);
    printf("           High Scores\n");
    for(int i = 0; i < 5; i++){
        printf("Number %d:                %d\n", i+1, scores[4-i]);
    }
}

//Takes the sorted list of scores and filename. Stores the list in the file.
void saveInFile(int* scores, char fileName[]){
    FILE* filePtr = fopen(fileName, "w");
    if (filePtr == NULL) {
        printf("Failed to open file");
        return;
    }

    for(int i = 0; i < 5; i++){
        fprintf(filePtr, "%d\n", scores[i]);
    }
    fclose(filePtr);
}

//Provides the complete functionality of the game.
void game_process(char difficulty){
    int score = 0;
    int* scorePtr = &score;
    int size = getSize(difficulty);
    int** grid = setBoard(size);
    generateRandomBlock(grid, size);
    generateRandomBlock(grid, size);
    do{
        char userMove = drawGameAndTakeInput(grid, size, score);
        if(userMove == 'Q'){
            printf("\nQuitting...\n");
            return;
        }
        if(move(userMove, grid, size, scorePtr)){
            generateRandomBlock(grid, size);
        }
    }while(!checkWin(grid, size) && !checkGameOver(grid, size));
    system("cls");
    drawBoard(grid, size, score);
    if(checkWin(grid, size)){
        printf("\nCoungratulations! You have won\n");
    }
    else{
        printf("\nGAME OVER!\n");
    }

    char filename[20];
    switch(difficulty){
        case 'E':
            strcpy(filename, "easy.txt");
            break;
        case 'M':
            strcpy(filename, "medium.txt");
            break;
        case 'H':
            strcpy(filename, "hard.txt");
    }
    int* highScores = getHighScores(filename);
    int index = saveHighScores(highScores, score);
    if(index != -1){
        printf("You have placed %d on the leaderboard!\n", 5 - index);
        saveInFile(highScores, filename);
    }
    displayHighScores(highScores, score);

    for(int i = 0; i < size; i++)
        free(grid[i]);
    free(highScores);
    free(grid);
}

int main(void){
    srand(time(0));
    char difficulty;
    while(difficulty != 'Q'){
        fflush(stdin);
        difficulty = drawMenuAndSelectDifficulty();
        if(difficulty != 'Q'){
            game_process(difficulty);
            fflush(stdin);
            printf("Enter any character to go to menu: ");
            getch();
            system("cls");
        }
    }
}