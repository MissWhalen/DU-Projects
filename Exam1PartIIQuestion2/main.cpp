#include <iostream>

int main() {
    int input;
    std::cout << "Enter an integer: " << "\n";
    std::cin >> input;

    for (int row = 0; row < input; row++) {
        int x = 0;
        int y = 0;
        if (x <= input && y <= input) {
            std::cout << "(" << x <<"," << y << ")""\n";
        }
        std::cout << "\n";
    }else{
        std::cout << "Not valid" << "\n";
    }


    return 0;
}
