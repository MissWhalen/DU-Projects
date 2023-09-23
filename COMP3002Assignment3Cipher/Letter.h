//
// Created by Briana on 2/16/2021.
//

#ifndef COMP3002ASSIGNMENT3CIPHER_LETTER_H
#define COMP3002ASSIGNMENT3CIPHER_LETTER_H


class Letter {
public:
    Letter(char c);

    friend char operator+(const Letter &lhs, const Letter &rhs);
    friend char operator-(const Letter &lhs, const Letter &rhs);

    friend bool operator==(const Letter &lhs, const Letter &rhs);

    friend bool operator!=(const Letter &lhs, const Letter &rhs);


    char c;
};

void test_addition();
void test_subtraction();

#endif //COMP3002ASSIGNMENT3CIPHER_LETTER_H
