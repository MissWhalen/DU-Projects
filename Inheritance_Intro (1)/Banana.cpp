//
// Created by Will on 2/3/2021.
//

#include "Banana.h"

std::ostream &operator<<(std::ostream &os, const Banana &banana) {
    os << "Banana";
    return os;
}

std::string Banana::getName() const {
    return "Banana";
}
