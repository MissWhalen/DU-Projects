//
// Created by Briana on 2/22/2021.
//

#ifndef COMP3002ASSIGNMENT4SHOPPINGCART_LYCHEE_H
#define COMP3002ASSIGNMENT4SHOPPINGCART_LYCHEE_H

#include "FruitPerPound.h"

class Lychee: public FruitPerPound {
public:
    Lychee(double weight);

    std::string getName() const override;
};


#endif //COMP3002ASSIGNMENT4SHOPPINGCART_LYCHEE_H
