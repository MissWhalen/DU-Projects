//
// Created by Briana on 11/20/2020.
//

#ifndef ASSINGMENT6NOTAKTO_NOTAKTOE_H
#define ASSINGMENT6NOTAKTO_NOTAKTOE_H
#include<vector>
#include<string>
#include<iostream>

std::vector<std::vector<char>> create_board();
void print_board(const std::vector<std::vector<char>> &board);
void read_move(int &a, int &b);
bool game_over(const std::vector<std::vector<char>> & board);
bool is_valid(const std::vector<std::vector<char>> & board, int row, int column);
void apply_move(std::vector<std::vector<char>> & board, int row, int column, int & current_player);
#endif //ASSINGMENT6NOTAKTO_NOTAKTOE_H
