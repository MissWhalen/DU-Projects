//
// Created by Will on 2/3/2021.
//

#include "Cart.h"

std::ostream &operator<<(std::ostream &os, const Cart &cart) {
    os << "Cart contents:\n";

    for (const auto &i : cart.contents) {
        os << *i << "\n";
    }

    return os;
}

void Cart::add(Item *i) {
    contents.push_back(i);
}
