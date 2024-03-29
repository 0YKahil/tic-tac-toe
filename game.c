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


int main() {
    char winner = ' ';
    char response = ' ';

    /* reset the board to its starting state */
    resetBoard();

    /* game loop */
    while (winner == ' ' && checkFreeSpaces() != 0) {
        showBoard();

        playerMove();
        winner = checkWinner();
        if (winner != ' ' || checkFreeSpaces() == 0) {
            break;
        }

        AIMove();
        winner = checkWinner();
        if (winner != ' ' || checkFreeSpaces() == 0) {
            break;
        }
    }

    showBoard();
    printWinner(winner);
    system("pause");
    return 0;
}

/*
 * MODIFIES: board
 * Resets the board back to the empty state with an empty char
 * as the value of every index in array
 */
void resetBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

/*
 * Prints the current state of the board to the console
 * with both players' positions
 */
void showBoard() {
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

/* Returns the number of free spaces left on the board */
int checkFreeSpaces() {
    int freeSpaces = 9;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != ' ') {
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}

/*
 * Takes input from player for x and y coordinates to insert the PLAYER char in
 * the given position. If the position is already filled, prompts the player again.
 */
void playerMove() {
    int x;
    int y;

    do {
        printf("Enter row #(1-3): ");
        scanf_s("%d", &x);
        x--;

        printf("Enter column #(1-3): ");
        scanf_s("%d", &y);
        y--;

        if (board[x][y] != ' ') {
            printf("Invalid Move!\n");
        }
        else {
            board[x][y] = PLAYER;
            break;
        }
    } while (board[x][y] != ' ');

}

/*
 * AI moves depending on decision tree on higher difficulty,
 * OR randomly selects a coordinate on lower difficulty
 */
void AIMove() {
    /* generate seed based on current time */
    srand(time(0));
    int x;
    int y;

    if (checkFreeSpaces > 0) {
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');

        board[x][y] = COMP;
    }
    else {
        printWinner(' ');
    }
}

/*
 * Runs through all win conditions to check if there is a winner,
 * Win conditions include:
 * an uninterrupted stream of 3 of the same character vertically,
 *                            3 of the same character horizontally,
 *                            3 of the same character diagonally.
 */
char checkWinner() {
    /* Checking horizontal win condition */
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            return board[i][0];
        }
    }

    /* Checking vertical win condition */
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == board[1][j] && board[0][j] == board[2][j]) {
            return board[0][j];
        }
    }

    /* Checking diagonal win condition */
    for (int k = 0; k < 3; k++) {
        if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
            return board[1][1];
        }

        if (board[2][0] == board[1][1] && board[2][0] == board[0][2]) {
            return board[1][1];
        }
    }

    /* no winner */
    return ' ';

}

void printWinner(char winner) {
    if (winner == PLAYER) {
        printf("\nYOU WIN!\n");
    }
    else if (winner == COMP) {
        printf("\nYOU LOSE!\n");
    }
    else {
        printf("\nDRAW!\n");
    }
}