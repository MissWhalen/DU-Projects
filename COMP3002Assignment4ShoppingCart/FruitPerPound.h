//
// Created by Briana on 2/22/2021.
//

#ifndef COMP3002ASSIGNMENT4SHOPPINGCART_FRUITPERPOUND_H
#define COMP3002ASSIGNMENT4SHOPPINGCART_FRUITPERPOUND_H
#include "Item.h"

class FruitPerPound: public Item {
public:
    double getPrice() const override;

    FruitPerPound(double price, double weight);

private:
    double price;
    double weight;

};


#endif //COMP3002ASSIGNMENT4SHOPPINGCART_FRUITPERPOUND_H
