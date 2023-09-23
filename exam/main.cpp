#include <iostream>

int main() {
    int x;
    std::cout << "Enter a positive number: " << "\n";
    std::cin >> x;
    if (x % 42 == 0) {
        std::cout << "X is a factor of 42" << "\n";
    } else {
        std::cout << "x is not a factor of 42" << "\n";
    }

    return 0;
}
