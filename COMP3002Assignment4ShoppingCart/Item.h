//
// Created by Briana on 2/22/2021.
//

#ifndef COMP3002ASSIGNMENT4SHOPPINGCART_ITEM_H
#define COMP3002ASSIGNMENT4SHOPPINGCART_ITEM_H
#include <iostream>

class Item {
public:
    virtual ~Item() = default;
    virtual double getPrice() const = 0;
    friend std::ostream &operator<<(std::ostream &os, const Item &item);

    // virtual permits a child class to provide its own implementation
    [[nodiscard]] virtual std::string getName() const = 0;
};


#endif //COMP3002ASSIGNMENT4SHOPPINGCART_ITEM_H
