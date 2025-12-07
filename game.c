#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

char board[3][3];

// ---------- BASIC BOARD FUNCTIONS ----------
void initialiseBoard() {
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            board[i][j] = ' ';
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
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(board[i][j] == ' ') return false;
    return true;
}

bool checkWin(char p) {
    for(int i = 0; i < 3; i++) {
        if(board[i][0]==p && board[i][1]==p && board[i][2]==p) return true;
        if(board[0][i]==p && board[1][i]==p && board[2][i]==p) return true;
    }
    if(board[0][0]==p && board[1][1]==p && board[2][2]==p) return true;
    if(board[0][2]==p && board[1][1]==p && board[2][0]==p) return true;

    return false;
}

void clearInputBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

// ---------- PLAYER MOVE ----------
void playerMove(char symbol) {
    int r, c;
    while(1) {
        printf("Player %c, enter row and column (0-2): ", symbol);
        if(scanf("%d %d", &r, &c) != 2) {
            printf("Invalid input.\n");
            clearInputBuffer();
            continue;
        }
        if(r<0 || r>2 || c<0 || c>2) {
            printf("Invalid position.\n");
        } else if(board[r][c] != ' ') {
            printf("Cell occupied.\n");
        } else {
            board[r][c] = symbol;
            clearInputBuffer();
            break;
        }
    }
}

// ----------------  AI EASY MODE  ----------------
void aiEasyMove() {
    int r, c;
    while(1) {
        r = rand() % 3;
        c = rand() % 3;
        if(board[r][c] == ' ') {
            board[r][c] = 'O';
            break;
        }
    }
}

// ----------------  AI MEDIUM MODE  ----------------
// Medium : If AI can win → win. If player can win → block. Else random.
bool tryWinningMove(char sym) {
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]==' ') {
                board[i][j] = sym;
                if(checkWin(sym)) return true;
                board[i][j] = ' ';
            }
        }
    }
    return false;
}

void aiMediumMove() {
    // Try winning
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]==' ') {
                board[i][j] = 'O';
                if(checkWin('O')) return;
                board[i][j] = ' ';
            }
        }
    }

    // Try blocking X
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]==' ') {
                board[i][j] = 'X';
                if(checkWin('X')) {
                    board[i][j] = 'O';
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // Random
    aiEasyMove();
}

// ---------------- AI HARD (MINIMAX) ----------------
int minimax(bool isAi) {
    if(checkWin('O')) return 10;
    if(checkWin('X')) return -10;
    if(isBoardFull()) return 0;

    int bestScore = isAi ? INT_MIN : INT_MAX;

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]==' ') {
                board[i][j] = isAi ? 'O' : 'X';
                int score = minimax(!isAi);
                board[i][j] = ' ';

                if(isAi)
                    if(score > bestScore) bestScore = score;
                else
                    if(score < bestScore) bestScore = score;
            }
        }
    }

    return bestScore;
}

void aiHardMove() {
    int best = INT_MIN, r=-1, c=-1;

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]==' ') {
                board[i][j] = 'O';
                int score = minimax(false);
                board[i][j] = ' ';

                if(score > best) {
                    best = score;
                    r = i; c = j;
                }
            }
        }
    }
    board[r][c] = 'O';
}

// ---------------- GAME MODES ----------------
void twoPlayerGame() {
    initialiseBoard();
    printBoard();

    while(1) {
        playerMove('X');
        printBoard();
        if(checkWin('X')) { printf("Player X wins!\n"); break; }
        if(isBoardFull()) { printf("Draw!\n"); break; }

        playerMove('O');
        printBoard();
        if(checkWin('O')) { printf("Player O wins!\n"); break; }
        if(isBoardFull()) { printf("Draw!\n"); break; }
    }
}

void aiGame(int difficulty) {
    initialiseBoard();
    printBoard();

    while(1) {
        playerMove('X');
        printBoard();
        if(checkWin('X')) { printf("You win!\n"); break; }
        if(isBoardFull()) { printf("Draw!\n"); break; }

        printf("AI thinking...\n");
        if(difficulty == 1) aiEasyMove();
        else if(difficulty == 2) aiMediumMove();
        else aiHardMove();

        printBoard();
        if(checkWin('O')) { printf("AI wins!\n"); break; }
        if(isBoardFull()) { printf("Draw!\n"); break; }
    }
}

// ---------------- MAIN MENU ----------------
int main() {
    srand(time(NULL));

    while(1) {
        printf("\n--- TIC TAC TOE MENU ---\n");
        printf("1. Play with Friend\n");
        printf("2. Play with AI\n");
        printf("3. Exit\n");
        printf("Choose option: ");

        int ch;
        scanf("%d", &ch);
        clearInputBuffer();

        if(ch == 1) {
            twoPlayerGame();
        }
        else if(ch == 2) {
            printf("Select Difficulty:\n1. Easy\n2. Medium\n3. Hard\nChoose: ");
            int d; 
            scanf("%d", &d);
            clearInputBuffer();
            aiGame(d);
        }
        else if(ch == 3) {
            printf("Goodbye!\n");
            break;
        }

        printf("\nPress Enter to return to menu...");
        getchar();
    }
    return 0;
}
