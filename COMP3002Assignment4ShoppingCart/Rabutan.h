//
// Created by Briana on 3/4/2021.
//

#ifndef COMP3002ASSIGNMENT4SHOPPINGCART_RABUTAN_H
#define COMP3002ASSIGNMENT4SHOPPINGCART_RABUTAN_H
#include "FruitPerPound.h"

class Rabutan: public FruitPerPound {
public:
    Rabutan(double weight);

    std::string getName() const override;
};


#endif //COMP3002ASSIGNMENT4SHOPPINGCART_RABUTAN_H
