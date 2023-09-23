//
// Created by Briana on 4/14/2021.
//

#ifndef COMP4370ASS2MERGFIB_VECTORS_H
#define COMP4370ASS2MERGFIB_VECTORS_H
#include <vector>
#include <iostream>
std::vector<int> random_numbers();

template <typename T>
void print(std::vector<T> const &a){
    for (const auto &item : a) {
        std::cout << item << ", ";
    }
    std::cout << "\n";

}


#endif //COMP4370ASS2MERGFIB_VECTORS_H
