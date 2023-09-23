//
// Created by Briana on 2/22/2021.
//

#include "ShoppingCart.h"
#include <iostream>
#include "Item.h"

std::ostream &operator<<(std::ostream &os, const ShoppingCart &cart) {
    os << "Cart contents:\n";

    for (const auto &i : cart.contents) {
        os << *i << "\n";
    }

    return os;
}

void ShoppingCart::add(std::unique_ptr<Item> i) {

    contents.push_back(std::move(i));
}

double ShoppingCart::checkout() {


    return 0;
}

double ShoppingCart::subtotal() {
    double sum = 0;
    for (const auto &i: contents) {
        sum += i->getPrice();
    }

    return sum;
}




