#include <iostream>
#include <string>
#include <cctype>

//function declarations
bool case_insensitive_equal(std::string a, std::string b);

void draw_square(int size);

void draw_box(int size);

void draw_diagonalup(int size);

void draw_diagonaldown(int size);

void draw_checkerboard(int size);

int promptSize(int min, int max);

int main() {
    //user input, size restrictions, function calls
    for (;;) {
        std::string command;
        std::cout << "Please enter a command: " << std::endl;
        std::cin >> command;
        if (case_insensitive_equal(command, "Square")) {
            draw_square(promptSize(1, 15));
        } else if (case_insensitive_equal(command, "box")) {
            draw_box(promptSize(3, 15));
        } else if (case_insensitive_equal(command, "diagonalup")) {
            draw_diagonalup(promptSize(3, 15));
        } else if (case_insensitive_equal(command, "diagonaldown")) {
            draw_diagonaldown(promptSize(3, 15));
        } else if (case_insensitive_equal(command, "checkerboard")) {
            draw_checkerboard(promptSize(5, 15));
        } else if (case_insensitive_equal(command, "help")) {
            std::cout << "Valid commands: Help, Quit, Square, Box, Diagonalup, Diagonaldown, Checkerboard" << std::endl;

        } else if (case_insensitive_equal(command, "quit")) {
            break;

        } else {
            std::cout << "Invalid Command" << std::endl;

        }
    }


    return 0;
}

// function definitions
bool case_insensitive_equal(std::string a, std::string b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (int i = 0; i < a.size(); ++i) {
        if (std::tolower(a[i]) != std::tolower(b[i])) {
            return false;
        }
    }
    return true;
}

void draw_square(int size) {
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            std::cout << "*";
        }
        std::cout << "\n";
    }
}

void draw_box(int size) {
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            if (row == 0 || col == 0 || row == size - 1 || col == size - 1) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}

void draw_diagonalup(int size) {
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            if (row + col == (size - 1)) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}

void draw_diagonaldown(int size) {
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            if (row == col) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}


void draw_checkerboard(int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (row % 2 == 0 && col % 2 == 0) {
                std::cout << "*";
            } else if (row % 2 != 0 && col % 2 != 0) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}

int promptSize(int min, int max) {
    for (;;) {
        std::cout << "Please enter a size between " << min << " and " << max << ":" << std::endl;
        int drawingSize;
        std::cin >> drawingSize;

        if (min <= drawingSize && drawingSize <= max) {
            return drawingSize;
        } else {
            std::cout << "Your input " << drawingSize << " is outside the valid range." << std::endl;
        }
    }
}