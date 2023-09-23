//
// Created by Briana on 2/22/2021.
//

#include "FruitPerPound.h"

double FruitPerPound::getPrice() const {
    return price * weight;
}

FruitPerPound::FruitPerPound(double price_, double weight_) : price(price_), weight(weight_){

}

