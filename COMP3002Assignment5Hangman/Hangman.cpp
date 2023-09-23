//
// Created by Briana on 3/17/2021.
//

#include <iostream>
#include "Hangman.h"


Hangman::Hangman(std::vector<std::string> initial_wordlist, int num_guesses) : words(initial_wordlist),
                                                                               guesses_remaining(num_guesses) {
// can skip initializing partitions
// need to set initial hint
current_hint = mask_word(words[0],"");
}

void Hangman::partition() {
    partitions.clear();
    // Use member variables words, and guessed_letters to overwrite member variable partitions
//if guessed letter is not in words partition to one group
//if guessed letter is in 1st position partition to one group ect.
    for (auto w: words) {
        partitions[mask_word(w, guessed_letters)].push_back(w);
    }
}

void testPartioning() {
//{abcd, abce, abdg} with guesses a,b
    {
        std::vector<std::string> words = {"abcd", "abce", "abdg"};
        std::string guesses = "ab";
        std::map<std::string, std::vector<std::string>> expected = {
                {"ab__", {"abcd", "abce", "abdg"}}
        };

        Hangman h(words);
        h.guessed_letters = guesses;

        h.partition();

        if (expected != h.partitions) {
            std::cout << "Error in partition(): words = {";
            for (const auto &w : words) {
                std::cout << w << ", ";
            }
            std::cout << "} guessed_letters = " << guesses << ". Expected:\n";
            for (const auto &pair : expected) {
                std::cout << pair.first << ": ";
                for (const auto &word : pair.second) {
                    std::cout << word << " ";
                }
                std::cout << "\n";
            }
            std::cout << "\nActual\n";
            for (const auto &pair : h.partitions) {
                std::cout << pair.first << ": ";
                for (const auto &word : pair.second) {
                    std::cout << word << " ";
                }
                std::cout << "\n";
            }
        }

    }
// {abcd, abce} with next guess of c
    {
        std::vector<std::string> words = {"abcd", "abde"};
        std::string guesses = "c";
        std::map<std::string, std::vector<std::string>> expected = {
                {"____", {"abde",}},
                {"__c_", {"abcd"}}
        };

        Hangman h(words);
        h.guessed_letters = guesses;

        h.partition();

        if (expected != h.partitions) {
            std::cout << "Error in partition(): words = {";
            for (const auto &w : words) {
                std::cout << w << ", ";
            }
            std::cout << "} guessed_letters = " << guesses << ". Expected:\n";
            for (const auto &pair : expected) {
                std::cout << pair.first << ": ";
                for (const auto &word : pair.second) {
                    std::cout << word << " ";
                }
                std::cout << "\n";
            }
            std::cout << "\nActual\n";
            for (const auto &pair : h.partitions) {
                std::cout << pair.first << ": ";
                for (const auto &word : pair.second) {
                    std::cout << word << " ";
                }
                std::cout << "\n";
            }
        }

    }
}

bool Hangman::is_valid_guess(std::string new_letter) {
    // return true iff new_letter is not present in guessed_letters

    if (guessed_letters.find(new_letter) == std::string::npos) {
        return true;

    }

    return false;
}

bool Hangman::apply_guess(std::string new_letter) {
    // return true iff guess was "correct"
    guessed_letters += new_letter;
    partition();
    // find largest partition
    std::string max = max_partition();
    words = partitions[max];
    // if key of largest partition differs from current_hint, then incorrect guess, else correct guess
    if (max != current_hint){
        current_hint = max;
        return true;
    }else{
        --guesses_remaining;
        return false;
    }
}

Hangman::game_over_options Hangman::is_game_over() {
    // return true iff guesses_remaining <= 0 or current_hint has no underscores
    if (guesses_remaining <= 0) {
        return game_over_options::loss;
    }
    if (current_hint.find('_') == std::string::npos) {
        return game_over_options::win;
    }
    return game_over_options::not_over;
}

std::ostream &operator<<(std::ostream &os, const Hangman &hangman) {
    os << "You have " << hangman.guesses_remaining << " incorrect guesses left.\n";
    os << "Current hint: " << hangman.current_hint << "\n";
    os << "Guessed letters: " << hangman.guessed_letters << "\n";

    return os;
}

std::string Hangman::max_partition() const {
    int max = 0;
    std::string max_key;
    for (auto pair: partitions) {
        if (pair.second.size() > max) {
            max = pair.second.size();
            max_key = pair.first;
        }
    }

    return max_key;
}

void Hangman::print_details() const {
std::cout << "The current words are: \n";
    for(auto i: words){
        std::cout << i << " ";
    }
    std::cout << "The partitions from the prior partition are: \n";
    for (const auto &pair : partitions) {
        std::cout << pair.first << ": ";
        for (const auto &word : pair.second) {
            std::cout << word << " ";
        }
        std::cout << "\n";
    }

}

const std::vector<std::string> &Hangman::getWords() const {
    return words;
}

std::string mask_word(const std::string &word, const std::string &guessed_letters) {
    std::string result;

    for (auto c: word) {
        if (guessed_letters.find(c) != std::string::npos) {
            result.push_back(c);
        } else {
            result.push_back('_');
        }
    }

    return result;
}

void testMasking() {
//if word zymurgy and letters guessed "rstne" then mask should be _______
    {
        std::string word = "zymurgy";
        std::string guessed_leters = "rstne";
        std::string expected = "____r__";
        std::string actual = mask_word(word, guessed_leters);
        if (actual != expected) {
            std::cout << "Error in mask_word. word = '" << word << "' guessed_letters = '" << guessed_leters
                      << "' expected = '" << expected << "' actual = '" << actual << "'\n";
        }
    }
    {
        std::string word = "zymurgy";
        std::string guessed_leters = "my";
        std::string expected = "_ym___y";
        std::string actual = mask_word(word, guessed_leters);
        if (actual != expected) {
            std::cout << "Error in mask_word. word = '" << word << "' guessed_letters = '" << guessed_leters
                      << "' expected = '" << expected << "' actual = '" << actual << "'\n";
        }
    }
//if word zymurgy and letters guessed "ym"  then mask should be  _ym___y

}