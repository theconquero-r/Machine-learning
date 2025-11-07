#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

char board[3][3];

void initialiseBoard() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    printf("\nCurrent Board:\n");
    for(int i = 0; i < 3; i++) {
        printf(" ");
        for(int j = 0; j < 3; j++) {
            printf("%c", board[i][j]);
            if(j < 2) printf(" | ");
        }
        printf("\n");
        if(i < 2) printf("---|---|---\n");
    }
    printf("\n");
}

bool isBoardFull() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] == ' ') return false;
        }
    }
    return true;
}

bool checkWin(char player) {
    for(int i = 0; i < 3; i++) {
        if((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
           (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            return true;
    }
    if((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
       (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        return true;
    return false;
}

int minimax(bool isAi);

void aiMove() {
    int bestScore = INT_MIN;
    int bestRow = -1, bestCol = -1;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] == ' ') {
                board[i][j] = 'O';
                int score = minimax(false);
                board[i][j] = ' ';
                if(score > bestScore) {
                    bestScore = score;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }
    board[bestRow][bestCol] = 'O';
}

int minimax(bool isAi) {
    if(checkWin('O')) return 10;
    if(checkWin('X')) return -10;
    if(isBoardFull()) return 0;

    if(isAi) {
        int bestScore = INT_MIN;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int score = minimax(false);
                    board[i][j] = ' ';
                    if(score > bestScore) bestScore = score;
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = INT_MAX;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int score = minimax(true);
                    board[i][j] = ' ';
                    if(score < bestScore) bestScore = score;
                }
            }
        }
        return bestScore;
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void playerMove() {
    int row, col;
    while(1) {
        printf("Enter your move (row and column, 0–2 each): ");
        if(scanf("%d %d", &row, &col) != 2) {
            printf("Invalid input. Please enter numbers.\n");
            clearInputBuffer();
            continue;
        }
        if(row < 0 || row > 2 || col < 0 || col > 2) {
            printf("Invalid move. Try again.\n");
        } else if(board[row][col] != ' ') {
            printf("Cell already occupied. Try again.\n");
        } else {
            board[row][col] = 'X';
            clearInputBuffer(); // to clear leftover input
            break;
        }
    }
}

int main() {
    initialiseBoard();
    printBoard();

    while(1) {
        playerMove();
        printBoard();
        if(checkWin('X')) {
            printf("Player wins!\n");
            break;
        }
        if(isBoardFull()) {
            printf("It's a draw!\n");
            break;
        }

        aiMove();
        printBoard();
        if(checkWin('O')) {
            printf("AI wins!\n");
            break;
        }
        if(isBoardFull()) {
            printf("It's a draw!\n");
            break;
        }
    }

    printf("\nPress Enter to exit...");
    getchar(); // keeps window open in VS Code
    return 0;
}
