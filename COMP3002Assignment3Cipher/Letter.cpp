//
// Created by Briana on 2/16/2021.
//

#include "Letter.h"
#include <iostream>

Letter::Letter(char c_) : c(c_) {

}

char operator+(const Letter &lhs, const Letter &rhs) {


    char plaintext_letter = static_cast<char> (std::toupper(lhs.c)) - 'A';

    char key_letter = static_cast<char>(std::toupper(rhs.c)) - 'A';


    char ciphertext_letter = static_cast<char>((plaintext_letter + key_letter) % 26);

    if (isupper(lhs.c)) {
        ciphertext_letter += 'A';
    } else {
        ciphertext_letter += 'a';
    }


    return ciphertext_letter;
}

bool operator==(const Letter &lhs, const Letter &rhs) {
    return lhs.c == rhs.c;
}

bool operator!=(const Letter &lhs, const Letter &rhs) {
    return !(lhs == rhs);
}

char operator-(const Letter &lhs, const Letter &rhs) {
    char plaintext_letter = static_cast<char> (std::toupper(lhs.c)) - 'A';

    char key_letter = static_cast<char>(std::toupper(rhs.c)) - 'A';


    char ciphertext_letter = static_cast<char>((plaintext_letter - key_letter +26) % 26);

    if (isupper(lhs.c)) {
        ciphertext_letter += 'A';
    } else {
        ciphertext_letter += 'a';
    }


    return ciphertext_letter;


}

void test_addition() {
    {
        Letter lhs('H');
        Letter rhs('K');
        Letter expected('R');
        Letter actual = lhs + rhs;

        if (actual != expected) {
            std::cout << "Error in addition with lhs = H and rhs = K expected R\n";
        }
    }
    {
        Letter lhs('o');
        Letter rhs('E');
        Letter expected('s');
        Letter actual = lhs + rhs;

        if (actual != expected) {
            std::cout << "Error in addition with lhs = o and rhs = E expected s\n";
        }
    }
    {
        Letter lhs('w');
        Letter rhs('Y');
        Letter expected('u');
        Letter actual = lhs + rhs;

        if (actual != expected) {
            std::cout << "Error in addition with lhs = w and rhs = Y expected u\n";
        }
    }
}

void test_subtraction() {
    {
        Letter lhs('R');
        Letter rhs('K');
        Letter expected('H');

        Letter actual = lhs - rhs;

        if (actual != expected) {
            std::cout << "Error in subtraction with lhs = R and rhs = K expected H\n";
        }
    }
    {
        Letter lhs('s');
        Letter rhs('E');
        Letter expected('o');
        Letter actual = lhs - rhs;

        if (actual != expected) {
            std::cout << "Error in subtraction with lhs = s and rhs = E expected o\n";
        }
    }
    {
        Letter lhs('u');
        Letter rhs('Y');
        Letter expected('w');
        Letter actual = lhs - rhs;

        if (actual != expected) {
            std::cout << "Error in subtraction with lhs = u and rhs = Y expected w\n";
        }
    }

}
