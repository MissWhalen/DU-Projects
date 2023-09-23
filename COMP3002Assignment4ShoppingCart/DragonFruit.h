//
// Created by Briana on 2/22/2021.
//

#ifndef COMP3002ASSIGNMENT4SHOPPINGCART_DRAGONFRUIT_H
#define COMP3002ASSIGNMENT4SHOPPINGCART_DRAGONFRUIT_H
#include "Item.h"

class DragonFruit: public Item {
public:
    double getPrice() const override;

    std::string getName() const override;
};


#endif //COMP3002ASSIGNMENT4SHOPPINGCART_DRAGONFRUIT_H
