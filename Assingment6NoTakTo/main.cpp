#include <iostream>
#include "NoTakToe.h"
#include <vector>


void Read_Move();

int main() {
    std::vector<std::vector<char>> board = create_board();
    int current_player = 1;
    //while the game is not over
    while (!game_over(board)) {
        //print the current board
        print_board(board);
        //read a move from the current player
        int row;
        int column;
        std::cout << "Player " << current_player << "\n";

        read_move(row, column);
        //if move is valid
        if (is_valid(board, row, column)) {
            //  apply the move and switch the current player
            apply_move(board, row, column, current_player);
            // if not then
        } else {
            //  print an error
            std::cout << "Invalid move " << "\n";
        }
    }
    print_board(board);
    std::cout << "\n";
    std::cout << "Player " << current_player << " wins\n";
    return 0;
}


void Read_Move() {
    int a;
    int b;
    read_move(a, b);

}