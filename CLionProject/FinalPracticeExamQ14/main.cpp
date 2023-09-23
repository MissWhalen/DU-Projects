#include <iostream>

void draw_patter();

int main() {
    draw_patter();
    return 0;
}

void draw_patter() {
    for (int row = 0; row <= 14; ++row) {
        for (int col = 0; col <= 14; ++col) {
            if (row == 0 || row == 14 || col == 0 || col == 14) {
                std::cout << "#";
            }else {
                for (row = 1; row < 7; row++) {
                    for (col = 1; col < row + 1; col++) {
                        std::cout << "*";
                    }
                    std::cout << "\n";

                }
                for (row = 1; row < 7; row++) {
                    for (col = row; col < 7; col++) {
                        std::cout << "*";
                        std::cout << "\n";
                    }
                }

            }
        }
    }
    std::cout << "\n";
}

