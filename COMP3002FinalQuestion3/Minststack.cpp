//
// Created by Briana on 3/20/2021.
//

#include "Minststack.h"
#include <vector>
#include <iostream>

void Minststack::push(int) {
    int x;
    int min;
    if (Stack.empty()) {
        x = min;
        //set value as min
        Stack.push_back(x);

    }
    if (!Stack.empty()) {
        //compare value to minValue
        //if new value is less than minValue store pointer to this location
        if (x < min) {
            min = x;
            MinStack.push_back(x);

        }else{
            Stack.push_back(x);
        }
    }
    //push value onto stack
}

void Minststack::pop() {
    if (!Stack.empty()) {
        Stack.pop_back();
    } else {
        std::cout << "Stack empty\n";
    }
}

int Minststack::min() {

MinStack.pop_back();
    return 0;
}
