#include <iostream>
#include <set>
#include <map>

#include "Words.h"
#include "Hangman.h"






int main() {
    testMasking();
    testPartioning();

    bool print_full_details = true;

    std::cout << "What word length do you want?" << std::endl;
    int wordLength;
    std::cin >> wordLength;
    auto initial_wordlist = read_file("words_alpha.txt", wordLength);
    std::cout << "The possible words are:\n";
    // loop to print out iniital_wordlist
    for(auto i: initial_wordlist){
        std::cout << i << " ";
    }
    Hangman game(initial_wordlist);
    while (game.is_game_over() == Hangman::game_over_options::not_over) {
        std::cout << game;

        if (print_full_details) {
            // call member function of hangmang that prints out partitions
            game.print_details();
        }

        std::cout << "What letter do you want to guess?\n";
        std::string guess;
        std::cin >> guess;

        // if valid guess, apply guess, else error
        std::cout << "You have guessed: " << guess << "\n";
        if (game.is_valid_guess(guess)){
            //apply move
            if (game.apply_guess(guess)){
                std::cout << "You have guessed correctly!\n";
            }else{
                std::cout << "Unfortunatley " << guess << " is not in the word\n";
            }

        } else{
            std::cout << "Not a valid guess\n";
        }




    }

    // Print out win/loss message
    // use is_game_over
    //if there is a loss, use words[0] as the "real" word
    if (game.is_game_over() == Hangman::game_over_options::loss){
        std::cout << "You have lost. The correct word was: \n";
        std::cout << game.getWords().at(0) <<"\n";

    }
    if(game.is_game_over() == Hangman::game_over_options::win){
        std::cout << "You Have Won!\n";
    }

    return 0;
}


