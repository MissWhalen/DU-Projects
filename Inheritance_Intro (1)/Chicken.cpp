//
// Created by Will on 2/3/2021.
//

#include "Chicken.h"

std::ostream &operator<<(std::ostream &os, const Chicken &chicken) {
    os << "Chicken";
    return os;
}

std::string Chicken::getName() const {
    return "Chicken";
}
