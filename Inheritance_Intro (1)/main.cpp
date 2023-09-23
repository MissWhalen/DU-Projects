#include <iostream>
#include "Banana.h"
#include "Chicken.h"
#include "Cart.h"

int main() {
    Banana b;
    std::cout << b << "\n";

    Chicken c;
    std::cout << c << "\n";

    Cart cart;
    std::cout << cart << "\n";

    cart.add(&b);
    cart.add(&c);

    std::cout << cart << "\n";

    Item &i = c;
    std::cout << i << "\n";

    return 0;
}
