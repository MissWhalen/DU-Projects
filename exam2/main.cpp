#include <iostream>

void draw_box(int size);

int main() {
    int size;
    std::cout << "enter pattern size" << "\n";
    std::cin >> size;
    draw_box(size);


    return 0;
}

void draw_box(int size) {
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            if (row % 3 == 0) {
                std::cout << "X";
            } else {
                if (row % 2 == 0 && col % 2 == 0) {
                    std::cout << "#";
                } else if (row % 2 != 0 && col % 2 != 0) {
                    std::cout << "#";
                } else {
                    std::cout << ".";
                }

            }
        }
        std::cout << "\n";
    }

}