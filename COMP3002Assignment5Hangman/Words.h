//
// Created by Briana on 3/14/2021.
//

#ifndef COMP3002ASSIGNMENT5HANGMAN_WORDS_H
#define COMP3002ASSIGNMENT5HANGMAN_WORDS_H

#include <iostream>
#include <vector>
#include <map>
#include <string>


std::vector<std::string> read_file(std::string filename, std::string::size_type size);

std::map<char, int> letter_histogram(std::vector<std::string> words);

std::map<char, std::vector<std::string>> find_words(std::vector<std::string> words, std::string guess);


#endif //COMP3002ASSIGNMENT5HANGMAN_WORDS_H
