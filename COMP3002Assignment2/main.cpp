#include <iostream>
#include "Cards.h"
#include "War.h"

double mean_hand_length10();

double mean_hand_length100();

double mean_hand_length1000();

int main() {
    //std::random_device rd;
    //std::mt19937 prng(rd());
    //MainDeck w(prng);
    //w.test_count_hand();
    //w.test_play_hand();
    std::cout << "With 10 games played the mean hand length was: " << mean_hand_length10();
    std::cout << "\n";
    std::cout << "With 100 games played the mean hand length was: " << mean_hand_length100();
    std::cout << "\n";
    std::cout << "With 1000 games played the mean hand length was: " << mean_hand_length1000();
    return 0;
}

double mean_hand_length10() {
    std::random_device rd;
    std::mt19937 prng(rd());
    int total_hands = 0;
    int num_trials = 10;
    for (int i = 0; i < num_trials; ++i) {
        MainDeck w(prng);
        total_hands += w.count_hands();
    }
    double mean = static_cast<double>(total_hands) / num_trials;
    return mean;
}

double mean_hand_length100() {
    std::random_device rd;
    std::mt19937 prng(rd());
    int total_hands = 0;
    int num_trials = 100;
    for (int i = 0; i < num_trials; ++i) {
        MainDeck w(prng);
        total_hands += w.count_hands();
    }
    double mean = static_cast<double>(total_hands) / num_trials;
    return mean;
}

double mean_hand_length1000() {
    std::random_device rd;
    std::mt19937 prng(rd());
    int total_hands = 0;
    int num_trials = 1000;
    for (int i = 0; i < num_trials; ++i) {
        MainDeck w(prng);
        total_hands += w.count_hands();
    }
    double mean = static_cast<double>(total_hands) / num_trials;
    return mean;
}