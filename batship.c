// Gali Hacohen
// 07/18/2024
// Making the game of Battleship

#include<stdio.h>
#include<stdbool.h>


#define SIZE 10
#define NAME_LEN 50
#define EASY_FILE "easy.txt"
#define MEDIUM_FILE "medium.txt"
#define HARD_FILE "hard.txt"

void initializeBoard(char board[][SIZE]);
void displayBoard(char board[][SIZE]);
int readShip(FILE* fp,FILE* fpointer, FILE* point, char board[][SIZE]);
int playingGame(char board[][SIZE],char boats[][SIZE]);
bool gameWon(char board[][SIZE], char boats[][SIZE]);
bool validMove(int rowI, int colI);

int main(){
int choice, playerTurn, shipSpots, difficulty;
char board[SIZE][SIZE], boat[SIZE][SIZE], playerName[NAME_LEN], playAgain;
FILE* fp, *fptr, *point;


printf("Enter in your name: ");
fgets(playerName, NAME_LEN, stdin);

printf("\n*** MAIN MENU***\n");
do{

printf("1. start Game\n");
printf("2. Exit Game\n");
scanf("%d", &choice);

switch(choice){

	case 1:


		printf("\n Enter difficulty \n");
		printf("1. Easy\n");
		printf("2. Medium\n");
		printf("3. Hard\n");
		scanf("%d", &difficulty);

		// Difficulty switch statment
		switch(difficulty){

		case 1:
	
			fp = fopen(EASY_FILE, "r");
			
		if(fp == NULL){
	
			printf("Cannot load game. Exiting...\n");
	
		return 0;
		}
		break;

		case 2:

			fptr = fopen(MEDIUM_FILE, "r");
		
		if(fptr == NULL){
	
			printf("Cannot load game. Exiting...\n");
	
		return 0;
		}

		break;

		case 3:

			point = fopen(HARD_FILE, "r");
		
		if(point == NULL){
	
			printf("Cannot load game. Exiting...\n");
	
		return 0;
			}
		break;

		default:

			printf("NOT A CHOICE\n");
		break;
		}		
		
		initializeBoard(board);
		displayBoard(board);
		shipSpots = readShip (fp, fptr, point, board);
		playingGame(board, board);
		fclose(fp);
		fclose(fptr);
		fclose(point);
	
	break;

	case 2:
		
		printf("Exiting game.");
	break;

	default:
		
		printf("INVALID CHOICE. PICK ANOTHER");
	break;
}

	printf("CONGRATULATIONS!!!\n");
	printf("It took you %d turns times for you to hit %d many boats \n", playerTurn, shipSpots);
	printf("This is your score %d!\n", 100 -playerTurn + shipSpots);
	
	printf("Play Again?");
	scanf(" %c", &playAgain);
}while(playAgain == 'Y' || playAgain == 'y');

return 0;
}
// first function
void initializeBoard(char board[][SIZE]){
	for(int row = 0; row < SIZE; row++){
		for(int col = 0; col< SIZE; col++){
			board[row][col] = ' ';
		}
	}
}

// second funtction
void displayBoard(char board[][SIZE]){
	
	printf(" A B C D E F G H I J \n");
	
	for(int row = 0; row < SIZE; row++){
		printf("%d ", row + 1);
	for(int col = 0; col < SIZE; col++){
		printf(" %c", board[row][col]);
		}printf("\n");
	}
}


// third function
int readShip(FILE* fp,FILE* fpointer, FILE* point, char board[][SIZE]){

int row, col, ships = 0;
char read;
	if(fp != NULL){
	for(row = 0; row < SIZE; row++){
		for(col = 0; col < SIZE; col++){
			fscanf(fp," %c",&board[row][col]);
			
			if(board[row][col] == 'S'){
				ships++;				
			}
		}
	}
}
	if(fpointer != NULL){
	for(row = 0; row < SIZE; row++){
		for(col = 0; col < SIZE; col++){
			fscanf(fpointer," %c",&board[row][col]);
			
			if(board[row][col] == 'S'){
				ships++;				
			}
		}
	}
}	
	if(point != NULL){
	for(row = 0; row < SIZE; row++){
		for(col = 0; col < SIZE; col++){
			fscanf(point," %c",&board[row][col]);
			
			if(board[row][col] == 'S'){
				ships++;				
			}
		}
	}
}
return ships;
}

// fourth function
int playingGame(char board[][SIZE],char boats[][SIZE]){

int row, col, fire = 0;
char colI;

	do{
		printf(" Fire Away!\n (Enter in a square on the grid like A1)");
		scanf(" %c%d", &colI, &row);
		
	while(!validMove(row, colI)){
		printf("Try Again!\n (Enter in a square on the grid like A1)");
		scanf(" %c%d", &colI, &row);
	}
	row--;
	col = colI - 'A'; 
	
	if(boats[row][col] == 'S'){
		
		board[row][col] = 'X';
	}else{
		board[row][col] = 'O';
	}
		fire++;
		
	}while(!gameWon(board, boats));

return fire;
}

// fifth function
bool gameWon(char board[][SIZE], char boats[][SIZE]){

	for(int row = 0; row < SIZE; row++){
		for(int col = 0; col < SIZE; col++){
			if(boats[row][col] == 'S' && board[row][col] == 'X'){
		return false;
			}
		}
	}
return true;
}

//sixth function
bool validMove(int rowI, int colI){
	if(colI < 'A' || colI > 'J'){
		printf("Invalid column letter \n");
		return false;
	}else if(rowI < 1 || rowI > SIZE){
		printf("Invalid row number \n");
		return false;
	}
return true;
}
