//
// Created by Briana on 2/22/2021.
//

#include "Item.h"
#include<iostream>

std::ostream &operator<<(std::ostream &os, const Item &item) {
    os << item.getName() << " $" << item.getPrice();
    return os;
}


