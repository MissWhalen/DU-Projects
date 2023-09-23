//
// Created by Briana on 3/4/2021.
//

#ifndef COMP3002ASSIGNMENT4SHOPPINGCART_MANGOSTEEN_H
#define COMP3002ASSIGNMENT4SHOPPINGCART_MANGOSTEEN_H
#include "Item.h"

class Mangosteen: public Item {
public:
    double getPrice() const override;

    std::string getName() const override;
};


#endif //COMP3002ASSIGNMENT4SHOPPINGCART_MANGOSTEEN_H
