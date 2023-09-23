//
// Created by Briana on 2/22/2021.
//

#include "Menu.h"
#include <iostream>
#include "ShoppingCart.h"
#include <cctype>
#include "DragonFruit.h"
#include "Lychee.h"
#include "Mangosteen.h"
#include "Rabutan.h"
#include "Guava.h"

void list();

void contents(ShoppingCart &cart);

void checkout(ShoppingCart &cart);

void add(ShoppingCart &cart);

double promptWeight();

bool case_insensitive_equal(std::string a, std::string b);

void menu() {
    std::cout << "Welcome to Miss B's Exotic Fruit Stand" << std::endl;
    std::cout << "Please select from the following options: " << std::endl;
    std::cout << "List, for your item selection " << std::endl;
    std::cout << "Add, to add an item to your cart " << std::endl;
    std::cout << "Contents, for your current shopping cart contents " << std::endl;
    std::cout << "Checkout, for your total balance " << std::endl;

    std::string command;
    ShoppingCart cart;

    for (;;) {
        std::cout << "Command: " << std::endl;
        std::cin >> command;
        if (case_insensitive_equal(command, "List")) { // print out list of all the products allow adding to cart
            list();
        } else if (case_insensitive_equal(command, "Contents")) { // print out contents of shopping cart
            contents(cart);
        } else if (case_insensitive_equal(command, "Checkout")) { // Checkout function from shopping cart class
            checkout(cart);
            break;
        } else if (case_insensitive_equal(command, "Add")) {
            add(cart);
        } else {
            std::cout << "Invalid command use: List, Add, Contents or Checkout \n";
        }

    }
}

bool case_insensitive_equal(std::string a, std::string b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (unsigned i = 0; i < a.size(); ++i) {
        if (std::tolower(a[i]) != std::tolower(b[i])) {
            return false;
        }
    }

    return true;
}

void list() {

    std::cout << "DragonFruit - $7.00 each\n";
    std::cout << "Guava - $6.00 each \n";
    std::cout << "Lychee  - $20.00 per pound\n";
    std::cout << "Mangosteen  - 8.00 each \n";
    std::cout << "Rabutan - $26.00 per pound \n";


}

void contents(ShoppingCart &cart) {
    std::cout << cart;
}

void checkout(ShoppingCart &cart) {
    std::cout << cart;

    double subtotal = cart.subtotal();
    double taxtotal = subtotal * 0.08845;
    double total = subtotal + taxtotal;

    std::cout << "Subtotal: $" << subtotal << std::endl;
    std::cout << "Tax: $" << taxtotal << std::endl;
    std::cout << "Total: $" << total << std::endl;
}

void add(ShoppingCart &cart) {
    std::cout << "Add Fruit: ";
    std::string item;
    std::cin >> item;
    if (case_insensitive_equal(item, "DragonFruit")) {
        cart.add(std::make_unique<DragonFruit>());
    } else if (case_insensitive_equal(item, "Lychee")) {
        cart.add(std::make_unique<Lychee>(promptWeight()));
    } else if (case_insensitive_equal(item, "Mangosteen")) {
        cart.add(std::make_unique<Mangosteen>());
    } else if (case_insensitive_equal(item, "Rabutan")) {
        cart.add(std::make_unique<Rabutan>(promptWeight()));
    } else if (case_insensitive_equal(item, "Guava")) {
        cart.add(std::make_unique<Guava>());
    } else {
        std::cout << "Not valid item";
    }
}

double promptWeight() {
    double weight;
    std::cout << "Number of pounds: ";
    std::cin >> weight;
    return weight;
}
