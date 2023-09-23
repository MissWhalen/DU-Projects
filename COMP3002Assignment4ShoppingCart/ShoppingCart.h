//
// Created by Briana on 2/22/2021.
//

#ifndef COMP3002ASSIGNMENT4SHOPPINGCART_SHOPPINGCART_H
#define COMP3002ASSIGNMENT4SHOPPINGCART_SHOPPINGCART_H

#include <iostream>
#include "Item.h"
#include <vector>
#include <memory>

class ShoppingCart {
public:
    double subtotal();

    friend std::ostream &operator<<(std::ostream &os, const ShoppingCart &cart);

// add item function
    void add(std::unique_ptr<Item> i);

// checkout function
    double checkout();

private:
    // contents
    std::vector<std::unique_ptr<Item>> contents;
//vector that stores the contents of the cart
};


#endif //COMP3002ASSIGNMENT4SHOPPINGCART_SHOPPINGCART_H
