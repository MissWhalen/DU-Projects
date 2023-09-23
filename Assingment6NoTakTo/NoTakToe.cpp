//
// Created by Briana on 11/20/2020.
//

#include "NoTakToe.h"
#include <iostream>
#include<string>

std::vector<std::vector<char>> create_board() {
    std::vector<std::vector<char>> result;

    for (int i = 0; i < 4; ++i) {
        std::vector<char> row;
        for (int j = 0; j < 4; ++j) {
            row.push_back('.');
        }
        result.push_back(row);
    }
    return result;
}

void print_board(const std::vector<std::vector<char>> &board) {
    for (const auto &row: board) {
        for (const auto &cell: row) {
            std::cout << cell;
        }
        std::cout << "\n";
    }

}

void read_move(int &a, int &b) {
    for (;;) {
        std::cout << "Enter a row and column: ";
        std::string a_str;
        std::string b_str;
        std::cin >> a_str;
        std::cin >> b_str;

        // Convert from string to int
        bool is_valid = true;
        try {
            a = std::stoi(a_str);
        } catch (std::invalid_argument &e) {
            std::cout << "The first value contained no number\n";
            is_valid = false;
        } catch (std::out_of_range &e) {
            std::cout << "The row is out of range\n";
            is_valid = false;
        }
        try {
            b = std::stoi(b_str);
        } catch (std::invalid_argument &e) {
            std::cout << "The second value contained no number\n";
            is_valid = false;
        } catch (std::out_of_range &e) {
            std::cout << "The column is out of range\n";
            is_valid = false;
        }

        if (!is_valid) {
            continue;
        }
        //bool is_valid = true; // flag
        if (a < 1 || a > 4) {
            std::cout << "That first value is out of range [1,4]\n";
            is_valid = false;
        }
        if (b < 1 || b > 4) {
            std::cout << "That second value is out of range [1,4]\n";
            is_valid = false;
        }

        if (is_valid) {
            a = a - 1;
            b = b - 1;
            return;
        }
    }

}

bool game_over(const std::vector<std::vector<char>> &board) {
    // Top row
    if (board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'X' && board[0][3] == 'X') {
        return true;
    }
    // Rest of rows, columns, and diagonals
    if (board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'X' && board[1][3] == 'X') {
        return true;
    }
    if (board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'X' && board[2][3] == 'X') {
        return true;
    }
    if (board[3][0] == 'X' && board[3][1] == 'X' && board[3][2] == 'X' && board[3][3] == 'X') {
        return true;
    }
    if (board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == 'X' && board[3][0] == 'X') {
        return true;
    }
    if (board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == 'X' && board[3][1] == 'X') {
        return true;
    }
    if (board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == 'X' && board[3][2] == 'X') {
        return true;
    }
    if (board[0][3] == 'X' && board[1][3] == 'X' && board[2][3] == 'X' && board[3][3] == 'X') {
        return true;
    }
    if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X' && board[3][3] == 'X') {
        return true;
    }
    if (board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'X' && board[0][3] == 'X') {
        return true;
    }
    if (board[0][3] == 'X' && board[1][2] == 'X' && board[2][1] == 'X' && board[3][0] == 'X') {
        return true;
    }

    return false;
}

bool is_valid(const std::vector<std::vector<char>> &board, int row, int column) {
    return board[row][column] == '.';
}

void apply_move(std::vector<std::vector<char>> &board, int row, int column, int &current_player) {

    board[row][column] = 'X';
    if (current_player == 1) {
        current_player = 2;
    } else {
        current_player = 1;
    }
}
