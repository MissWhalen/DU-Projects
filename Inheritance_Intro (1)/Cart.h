//
// Created by Will on 2/3/2021.
//

#ifndef INHERITANCE_CART_H
#define INHERITANCE_CART_H


#include <ostream>
#include <vector>

#include "Item.h"

class Cart {
public:
    friend std::ostream &operator<<(std::ostream &os, const Cart &cart);

    void add(Item *i);

private:
    std::vector<Item *> contents;
};


#endif //INHERITANCE_CART_H
