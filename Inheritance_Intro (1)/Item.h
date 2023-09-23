//
// Created by Will on 2/3/2021.
//

#ifndef INHERITANCE_ITEM_H
#define INHERITANCE_ITEM_H


#include <ostream>
#include <string>

// Base class / Parent class
class Item {
public:
    friend std::ostream &operator<<(std::ostream &os, const Item &item);

    // virtual permits a child class to provide its own implementation
    virtual std::string getName() const;

};


#endif //INHERITANCE_ITEM_H
