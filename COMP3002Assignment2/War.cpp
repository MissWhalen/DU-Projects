//
// Created by Briana on 1/27/2021.
//

#include "War.h"
#include "Cards.h"
#include <iostream>
#include <algorithm>
#include <random>

MainDeck::MainDeck(std::mt19937 &twister_):twister(twister_) {
    auto deck = create_deck();
    shuffle(deck);
    deal(deck);


}

std::ostream &operator<<(std::ostream &os, const MainDeck &deck) {
    // os << "deck: " << deck.deck;
    os << "player 1: " << deck.player1_deck.size();
    for (const auto &i:deck.player1_deck) {
        os << i;
    }
    os << "\n";

    os << "player 2: " << deck.player2_deck.size();

    for (const auto &i:deck.player2_deck) {
        os << i;
    }
    return os;
}

std::vector<Cards> MainDeck::create_deck() const {
    std::vector<Cards> deck;

    for (int i = 0; i < 4; ++i) {
        for (int j = 2; j <= 14; ++j) {
            deck.emplace_back(static_cast<Cards::Suits>(i), static_cast<Cards::FaceValue>(j));
        }
    }
    return deck;
}

void MainDeck::shuffle(std::vector<Cards> &card_pile) const {

// Shuffle


    std::shuffle(card_pile.begin(), card_pile.end(), twister);

}
// deal half the deck to each player
void MainDeck::deal(std::vector<Cards> deck) {
    while (!deck.empty()) {
        player1_deck.push_back(deck.back());
        deck.pop_back();
        player2_deck.push_back(deck.back());
        deck.pop_back();
    }

}
// count the cards in each players hands
int MainDeck::count_hands() {
    int count = 0;
    while (!player1_deck.empty() && !player2_deck.empty()) {
        play_hand();
        ++count;
    }

    return count;
}

void MainDeck::play_hand() {
   int winner = 0;
    std::vector<Cards> common_pool;
    while (winner == 0) {
        // Ensure both players have cards to play
        if (player1_deck.empty() || player2_deck.empty()) {
            return;
        }

        // Determine who the winner is
        if (player1_deck.front() > player2_deck.front()) {
            winner = 1;
            //std::cout << "Player 1 Wins!" << "\n";

        } else if (player1_deck.front() == player2_deck.front()) {
            winner = 0;
        } else {
            winner = 2;
            //std::cout << "Player 2 Wins!" << "\n";
        }

        // Remove cards from each player to the common pool from front of deck
        common_pool.push_back(player1_deck.front());
        player1_deck.pop_front();
        common_pool.push_back(player2_deck.front());
        player2_deck.pop_front();
    }

    // Shuffle cards from the common pool
    shuffle(common_pool);
    // Give the common pool to the winner's deck at the back
    if (winner == 1) { // player one is the winner
        while (!common_pool.empty()) {
            player1_deck.push_back(common_pool.back());
            common_pool.pop_back();
        }
    } else { // Player 2 is the winner
        while (!common_pool.empty()) {
            player2_deck.push_back(common_pool.back());
            common_pool.pop_back();
        }
    }
}




void MainDeck::test_play_hand() {
    std::random_device rd;
    std::mt19937 prng(rd());
    {
        MainDeck t(prng);
        t.player1_deck = {Cards(Cards::Suits::Heart, Cards::FaceValue::three)};
        t.player2_deck = {Cards(Cards::Suits::Heart, Cards::FaceValue::four)};
        t.play_hand();

        if (!t.player1_deck.empty() || t.player2_deck.size() != 2) {
            std::cout << "Error: player1_deck should be empty and player2_deck to have 2 cards" << "\n";
            std::cout << t;
        }
    }
    {
        MainDeck t(prng);
        t.player1_deck = {Cards(Cards::Suits::Heart, Cards::FaceValue::three),
                          (Cards(Cards::Suits::Heart, Cards::FaceValue::two))};
        t.player2_deck = {Cards(Cards::Suits::Heart, Cards::FaceValue::four),
                          (Cards(Cards::Suits::Heart, Cards::FaceValue::five))};
        t.play_hand();

        if (t.player1_deck.size() !=1 || t.player2_deck.size() != 3) {
            std::cout << "Error: player1_deck should have 1 card and player2_deck to have 3 cards" << "\n";
            std::cout << t;
        }
    }
}

void MainDeck::test_count_hand() {
    std::random_device rd;
    std::mt19937 prng(rd());

    {
        MainDeck t(prng);
        t.player1_deck = {Cards(Cards::Suits::Heart, Cards::FaceValue::three),
                          (Cards(Cards::Suits::Heart, Cards::FaceValue::six),
                          (Cards(Cards::Suits::Heart, Cards::FaceValue::two)))};
        t.player2_deck = {Cards(Cards::Suits::Heart, Cards::FaceValue::four),
                          (Cards(Cards::Suits::Heart, Cards::FaceValue::five))};
        t.play_hand();

        if (t.player1_deck.size() !=1 || t.player2_deck.size() != 3) {
            std::cout << "Error: player1_deck should have 2 card and player2_deck to have 3 cards" << "\n";
            std::cout << t;
        }
    }
}


