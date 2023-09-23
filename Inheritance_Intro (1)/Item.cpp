//
// Created by Will on 2/3/2021.
//

#include "Item.h"

std::ostream &operator<<(std::ostream &os, const Item &item) {
    os << item.getName();
    return os;
}

std::string Item::getName() const {
    return "Item";
}
