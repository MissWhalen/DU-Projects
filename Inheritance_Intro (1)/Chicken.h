//
// Created by Will on 2/3/2021.
//

#ifndef INHERITANCE_CHICKEN_H
#define INHERITANCE_CHICKEN_H


#include <ostream>

#include "Item.h"

// Chicken is a child class of Item
class Chicken : public Item {
public:
    friend std::ostream &operator<<(std::ostream &os, const Chicken &chicken);

    std::string getName() const override;
};


#endif //INHERITANCE_CHICKEN_H
