#include <iostream>

// function declarations
void buildTruncatablePrimes(int start);

bool is_prime(int candidate);

bool is_left_truncatable(int candidate);

void test_is_left_truncatable();

int main() {
    //building with individual prime numbers
    //test_is_left_truncatable();
    buildTruncatablePrimes(2);
    buildTruncatablePrimes(3);
    buildTruncatablePrimes(5);
    buildTruncatablePrimes(7);
    return 0;
}

bool is_prime(int candidate) {
    //ruling out negative numbers
    if (candidate < 2) {
        return false;
    }
    //including 2 in as prime
    if (candidate == 2) {
        return true;
    }
    //ruling out even numbers
    if (candidate % 2 == 0) {
        return false;
    }
    //testing odd numbers
    for (int divisor = 3; divisor < candidate; divisor += 2) {
        if (candidate % divisor == 0) {
            return false;
        }
    }
    return true;
}

void buildTruncatablePrimes(int start) {
    if (!is_prime(start)) {
        return;
    }

    if (is_left_truncatable(start)) {
        std::cout << start << "\n";
    }
    buildTruncatablePrimes(start * 10 + 1);
    buildTruncatablePrimes(start * 10 + 3);
    buildTruncatablePrimes(start * 10 + 7);
    buildTruncatablePrimes(start * 10 + 9);
}

bool is_left_truncatable(int candidate) {
    for (int i = 10; i < candidate; i *= 10) {
        if (!is_prime(candidate % i)) {
            return false;
        }
    }
    return is_prime(candidate);
}

void test_is_left_truncatable() {
    if (is_left_truncatable(10)) {
        std::cout << " 10 not left truncatable" << "\n";
    }
    if (!is_left_truncatable(313)) {
        std::cout << "313 is left truncatable" << "\n";
    }
}