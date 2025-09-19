import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class TicTacToeGUI {
    static char[][] board = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    static JButton[][] buttons = new JButton[3][3];

    public static void main(String[] args) {
        initialiseBoard();
        createAndShowGUI();
    }

    public static void initialiseBoard() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                board[i][j] = ' ';
    }

    public static void createAndShowGUI() {
        JFrame frame = new JFrame("Tic Tac Toe");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 400);
        frame.setLayout(new GridLayout(3,3));

        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                JButton button = new JButton(" ");
                button.setFont(new Font("Arial", Font.BOLD, 60));
                final int row = i;
                final int col = j;

                button.addActionListener(e -> {
                    if(button.getText().equals(" ") && !checkWin('X') && !checkWin('O')){
                        button.setText("X");
                        board[row][col] = 'X';

                        if(checkWin('X')){
                            JOptionPane.showMessageDialog(frame, "Player wins!");
                        } else if(isBoardFull()){
                            JOptionPane.showMessageDialog(frame, "It's a draw!");
                        } else {
                            aiMove();
                            updateButtons();
                            if(checkWin('O')){
                                JOptionPane.showMessageDialog(frame, "AI wins!");
                            } else if(isBoardFull()){
                                JOptionPane.showMessageDialog(frame, "It's a draw!");
                            }
                        }
                    }
                });

                buttons[i][j] = button;
                frame.add(button);
            }
        }

        frame.setVisible(true);
    }

    public static void updateButtons(){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                buttons[i][j].setText(String.valueOf(board[i][j]));
            }
        }
    }

    public static boolean isBoardFull(){
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(board[i][j]==' ')
                    return false;
        return true;
    }

    public static boolean checkWin(char player){
        for(int i=0;i<3;i++){
            if((board[i][0]==player && board[i][1]==player && board[i][2]==player) ||
               (board[0][i]==player && board[1][i]==player && board[2][i]==player))
                return true;
        }
        if((board[0][0]==player && board[1][1]==player && board[2][2]==player) ||
           (board[0][2]==player && board[1][1]==player && board[2][0]==player))
            return true;

        return false;
    }

    public static void aiMove(){
        int bestScore = Integer.MIN_VALUE;
        int bestRow=-1, bestCol=-1;

        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j]==' '){
                    board[i][j]='O';
                    int score = minimax(false);
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
        if(checkWin('O')) return 10;
        if(checkWin('X')) return -10;
        if(isBoardFull()) return 0;

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
