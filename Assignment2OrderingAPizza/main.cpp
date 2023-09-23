//Briana Whalen
//Bridge Course: C and C++
//Assignment 2: Ordering a Pizza
#include <iostream>
#include <string>

int main() {
    // read in user input
    std::cout << "How many pizzas would you like?" << std::endl;
    int numPizzas;
    std::cin >> numPizzas;

    double subtotal = 0;


    for (int i = 0; i < numPizzas; i++) {

        std::cout << "For Pizza " << i + 1 << std::endl;
        std::string pizzaSize;
        std::cout << "What size pizza would you like? (Small, Medium, Large):" << std::endl;
        std::cin >> pizzaSize;
        std::cout << "How many toppings would you like?" << std::endl;
        int toppings;
        std::cin >> toppings;
        std::string sauce;
        std::cout << "Would you like extra sauce for $0.50? (Y/N):" << std::endl;
        std::cin >> sauce;
        //Calculations for pizza prices
        double perPizzaCost;
        if (pizzaSize == "Small") {
            perPizzaCost = 7 + (toppings * 0.5);
        } else if (pizzaSize == "Medium"){
            perPizzaCost = 10.75 + (toppings * 1.0);
        }else{
            perPizzaCost = 14.75 + (toppings * 1.50);
        }
        if (sauce == "Y"){
            perPizzaCost += 0.5;
        }
        subtotal += perPizzaCost;
        // Output for pizza calculations
        std::cout << "Your " << pizzaSize << " pizza with " << toppings << " toppings is: $"
                  << perPizzaCost << std::endl;

    }

    double taxTotal = subtotal * 0.04;
    double total = subtotal + taxTotal;

    std::cout << "Subtotal: $" << subtotal << std::endl;
    std::cout << "Tax: $" << taxTotal << std::endl;
    std::cout << "Total: $"<< total << std::endl;



    return 0;
}
