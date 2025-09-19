import java.util.Scanner;
public class tic_tac_toe {
    static char[][] board = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    public static void main(String[] args) {
        initialiseBoard();
        printBoard();
        while(true){
            playerMove();
            printBoard();
            if(checkWin('X')){
                System.out.println("Player wins!");
                break;
            }
            if(isBoardFull()){
                System.out.println("It's a draw!");
                break;
            }
            aiMove();
            printBoard();
            if(checkWin('O')){
                System.out.println("AI wins!");
                break;
            }
            if(isBoardFull()){
                System.out.println("It's a draw!");
                break;
            }
        }
    }
    public static void initialiseBoard() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = ' ';
            }
        }
    }
    public static void printBoard() {
        System.out.println("Current Board:");
        for (int i = 0; i < 3; i++) {
            System.out.print(" ");
            for(int j=0;j<3;j++){
                System.out.print(board[i][j]);
                if(j<2){
                    System.out.print(" | ");
                }
            }
            System.out.println();
            if(i<2){
                System.out.println("---|---|---");
            }
        }
    }

    public static boolean isBoardFull(){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j]==' '){
                    return false;
                }
            }
        }
        return true;
    }

    static Scanner sc = new Scanner(System.in);
    public static void playerMove(){
        int row, col;
        while(true){
            System.out.println("Enter your move (row and column) separated by spaces : ");
            String input=sc.nextLine();
            String parts[]=input.trim().split("\\s+");
            if(parts.length!=2){
                System.out.println("Invalid input. Please enter two numbers separated by spaces .");
                continue;
            }
            try{
                row=Integer.parseInt(parts[0]);
                col=Integer.parseInt(parts[1]);
            }
            catch(NumberFormatException e){
                System.out.println("Invalid input. Please enter numeric values.");
                continue;
            }
            if(row<0 || row>2 || col<0 || col>2){
                System.out.println("Invalid move. Try again.");
            }else if(board[row][col]!=' '){
                System.out.println("Cell already occupied. Try again.");
            }else{
                board[row][col] = 'X';
                break;
            }
        }
    }

    public static boolean checkWin(char player){
        // Check rows and columns
        for(int i=0;i<3;i++){
            if((board[i][0]==player && board[i][1]==player && board[i][2]==player) ||
               (board[0][i]==player && board[1][i]==player && board[2][i]==player)){
                return true;
            }
        }
        // Check diagonals
        if((board[0][0]==player && board[1][1]==player && board[2][2]==player) ||
           (board[0][2]==player && board[1][1]==player && board[2][0]==player)){
            return true;
        }
        return false;
    }

    public static void aiMove(){
        int bestScore=Integer.MIN_VALUE;
        int bestRow=-1;
        int bestCol=-1;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j]==' '){
                    board[i][j]='O';
                    int score=minimax(false);
                    board[i][j]=' ';
                    if(score>bestScore){
                        bestScore=score;
                        bestRow=i;
                        bestCol=j;
                    }
                    
                }
            }
        }
        board[bestRow][bestCol]='O';
    }

    public static int minimax(boolean isAi){
        if(checkWin('O')){
            return 10;
        }
        if(checkWin('X')){
            return -10;
        }
        if(isBoardFull()){
            return 0;
            }
        if(isAi){
            int bestScore=Integer.MIN_VALUE;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    if(board[i][j]==' '){
                        board[i][j]='O';
                        int score=minimax(false);
                        board[i][j]=' ';
                        bestScore=Math.max(score,bestScore);    
                    }
                }
        }

        return bestScore;
    }else{
        int bestScore=Integer.MAX_VALUE;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j]==' '){
                    board[i][j]='X';
                    int score=minimax(true);
                    board[i][j]=' ';
                    bestScore=Math.min(score,bestScore);
                }
            }
        }
        return bestScore;
    }
    }
}




