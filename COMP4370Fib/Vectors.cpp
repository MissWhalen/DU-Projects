//
// Created by Briana on 4/14/2021.
//

#include "Vectors.h"
#include <random>

std::vector<int> random_numbers(){
    std::random_device rd;
    std::mt19937 prng(rd());
    std::uniform_int_distribution<> distribution(1, 100);
    std::vector<int> result;
    for (int i = 0; i < 10; ++i) {
        result.push_back(distribution(prng));
    }
    return result;
}


