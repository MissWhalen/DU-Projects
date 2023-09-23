#include <iostream>
#include <cmath>
#include <cctype>

int sum(int input);

int main() {
    for (;;) {
        int input;
        std::cout << "Enter a number: " << "\n";
        std::cin >> input;
        if (input > 0){
        std::cout << input << "\n";
        }else{
           std::cout << int sum(int input) << "\n";
            break;
        }
    }
    return 0;
}

int sum(int input){
    if (input % 2){
        std::cout << sum +=input;
    }
}