//
// Created by Will on 2/3/2021.
//

#ifndef INHERITANCE_BANANA_H
#define INHERITANCE_BANANA_H


#include <ostream>

#include "Item.h"

class Banana : public Item {
public:
    std::string getName() const override;

    friend std::ostream &operator<<(std::ostream &os, const Banana &banana);

};


#endif //INHERITANCE_BANANA_H
