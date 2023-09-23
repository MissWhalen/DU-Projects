//
// Created by Briana on 1/27/2021.
//

#ifndef COMP3002ASSIGNMENT2_WAR_H
#define COMP3002ASSIGNMENT2_WAR_H

#include "Cards.h"
#include <iostream>
#include <vector>
#include <list>
#include <random>

class MainDeck {
public:
    MainDeck(std::mt19937 &twister);

    int count_hands();

    void play_hand();

    void test_play_hand();

    void test_count_hand();

    friend std::ostream &operator<<(std::ostream &os, const MainDeck &deck);


private:
    std::vector<Cards> create_deck() const;

    std::mt19937 &twister;
    void shuffle(std::vector<Cards> &card_pile) const;

    std::list<Cards> player1_deck;
    std::list<Cards> player2_deck;

    void deal(std::vector<Cards> deck);
};


#endif //COMP3002ASSIGNMENT2_WAR_H
