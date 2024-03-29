#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

/* 3 by 3 2d array representing the board */
char board[3][3];
const char PLAYER = 'X';
const char COMP = 'O';
bool hardMode = false;

void resetBoard();
void showBoard();
int checkFreeSpaces();
void playerMove();
void AIMove();
char checkWinner();
void printWinner(char);

void main() {
	printf("Hello World, From C! \n");
}