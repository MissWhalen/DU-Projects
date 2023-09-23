//
// Created by Briana on 3/17/2021.
//

#ifndef COMP3002ASSIGNMENT5HANGMAN_HANGMAN_H
#define COMP3002ASSIGNMENT5HANGMAN_HANGMAN_H
//#include "Words.h"

#include <map>
#include <string>
#include <vector>
#include <ostream>

class Hangman {
public:
    Hangman(std::vector<std::string> initial_wordlist, int num_guesses = 5);
//current word list
//start with words of wordLength
//update currentWordList with each guess
//add each letter guessed


//guessed letters
    friend std::ostream &operator<<(std::ostream &os, const Hangman &hangman);

//masking
//use current word list
//iterate trough words to see if the guessed letter is in the word
//reveal guessed letter

bool is_valid_guess(std::string new_letter);
bool apply_guess(std::string new_letter);
enum class game_over_options {
    win, loss, not_over
};
game_over_options is_game_over();
std::string max_partition() const;
void print_details() const;

//partitioning
    void partition();
    friend void testPartioning();
//current words
//letters guessed to partition out words
private:
    std::map<std::string, std::vector<std::string>> partitions;
    std::vector<std::string> words;
public:
    const std::vector<std::string> &getWords() const;

private:
    int guesses_remaining;
    std::string guessed_letters;
    std::string current_hint;


};

void testPartioning();

std::string mask_word(const std::string &word, const std::string &guessed_letters);
void testMasking();


#endif //COMP3002ASSIGNMENT5HANGMAN_HANGMAN_H
