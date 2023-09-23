//
// Created by Briana on 3/4/2021.
//

#include "Rabutan.h"


std::string Rabutan::getName() const {
    return "Rabutan";
}

Rabutan::Rabutan(double weight_a) : FruitPerPound(26, weight_a) {}
