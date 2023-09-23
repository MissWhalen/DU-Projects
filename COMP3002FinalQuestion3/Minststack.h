//
// Created by Briana on 3/20/2021.
//

#ifndef COMP3002FINALQUESTION3_MINSTSTACK_H
#define COMP3002FINALQUESTION3_MINSTSTACK_H

#include<vector>
#include "Node.h"

class Minststack {
public:
void pop();
void push(int value);
int min() ;


    std::vector<int> Stack;
    std::vector<int> MinStack;
};


#endif //COMP3002FINALQUESTION3_MINSTSTACK_H
