#include <iostream>

int find_boundary(std::string message, int start);

void test_find_boundary();

int main() {
    test_find_boundary();
    return 0;
}

// Count how many characters after start you need to travel to find 8 alphabetic characters
// If not enough are found, return -1
int find_boundary(std::string message, int start) {
    int offset = 0;
    int remaining = 8;
    //while there are remaining characters
    while (remaining > 0) {
        //if start + offset >= length of message
        if (start + offset >= message.length()) {
            return -1;
        }
        //if message[start + offset] is an alphabetic character decrement remaining increment offset
        if (std::isalpha(message[start + offset])) {
            --remaining;
        }
        ++offset;

    }
    return offset;
}

void test_find_boundary() {
    //message"abcdefgh" starting at 0 should be 8
    if (find_boundary("abcdefgh", 0) != 8) {
        std::cout << "Error find_boundary of 'abcdefgh' starting at 0 doesn't return 8" << "\n";
    }
    if (find_boundary("abc   defgh", 0) != 11) {
        std::cout << "Error find_boundary of \"abc   defgh\" with a start of 0 doesn't return 11" << "\n";
    }
    if (find_boundary("Few quips galvanized the mock jury box.", 0) != 9) {
        std::cout
                << "Error find_boundary of \"Few quips galvanized the mock jury box.\" with a start of 0 doesn't return 9"
                << "\n";
    }
    if (find_boundary("Few quips galvanized the mock jury box.", 9) != 9) {
        std::cout
                << "Error find_boundary of \"Few quips galvanized the mock jury box.\" with a start of 9 doesn't return 9"
                << "\n";
    }
    if (find_boundary("Few quips galvanized the mock jury box.", 18) != 10) {
        std::cout
                << "Error find_boundary of \"Few quips galvanized the mock jury box.\" with a start of 18 doesn't return 10"
                << "\n";
    }
    if (find_boundary("Few quips galvanized the mock jury box.", 28) != 10) {
        std::cout
                << "Error find_boundary of \"Few quips galvanized the mock jury box.\" with a start of 0 doesn't return 9"
                << "\n";
    }
}