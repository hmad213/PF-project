#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>

//struct for each block on the grid
struct block{
    int value;
    int cords[2];
};

//Takes the input of the difficulty of the game from the user. Returns a char from 'E', 'M' or 'H'
char input(){
    
}

//Takes a difficulty level ('E', 'M', 'H') and returns a grid of Block structures sized according to the difficulty
struct block** set_difficulty(char difficulty){

}

//Takes a grid and prints the board
void draw_board(struct block** grid){

}

//Takes the input of the move of the user. Returns a char from 'W', 'A', 'S', 'D'
char take_input(){

}

//Takes a move ('W', 'A', 'S', 'D') and returns 1 if a move is successful otherwise returns 0
int move(char move){

}

//Takes a grid and returns an array of all the blocks that are empty
struct block* get_empty_spaces(struct block** grid){

}

//Takes a grid and returns 1 if the game is over and 0 if not
int check_game_over(struct block** grid){

}

//DEFINITION UNFINISHED. Takes a difficulty('E', 'M', 'H') and gets data from the appropriate text file
void get_high_scores(char difficulty){

}

//DEFINITION UNFINISHED. Takes a score, checks if it is a high score, and saves it appropriately 
void save_high_scores(){

}

int main(void){
    
}