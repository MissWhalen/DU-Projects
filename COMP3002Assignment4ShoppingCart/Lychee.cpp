//
// Created by Briana on 2/22/2021.
//

#include "Lychee.h"


std::string Lychee::getName() const {
    return "Lychee";
}

Lychee::Lychee(double weight_) : FruitPerPound(20, weight_) {}
