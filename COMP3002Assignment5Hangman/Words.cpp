//
// Created by Briana on 3/14/2021.
//

#include "Words.h"
#include <iostream>
#include <fstream>

std::vector<std::string> read_file(std::string filename, std::string::size_type size) {
    std::ifstream file{filename};

    if (!file.is_open()) {
        std::cout << "Could not open " << filename << "\n";
    }

    std::vector<std::string> words;

    while (!file.eof()) {
        std::string word;
        file >> word;
        if (word.size() == size) {
            words.push_back(word);
        }
    }
    return words;
}

std::map<char, int> letter_histogram(std::vector<std::string> words) {
    std::map<char, int> results;

    for (const auto &word : words) {
        for (const auto &letter : word) {
            ++results[letter];
        }
    }

    return results;
}

std::map<char, std::vector<std::string>> find_words(std::vector<std::string> words, std::string guess) {
    std::map<char, std::vector<std::string>> results;

    for (const auto &word : words) {
        for (const auto &letter : word) {
            if (guess.find(letter) != std::string::npos) {
                results[letter].push_back(word);
                break;
            }
        }

    }

    return results;
}
