#include <iostream>
#include <vector>
#include <cmath>


bool is_prime(int candidate);

void test_is_prime();

int main() {
    test_is_prime();

    is_prime(2'147'483'647);

    return 0;
}


bool is_prime(int candidate) {
    // Primes must be at least 2 so "candidate" LESS than 2 should return false
    // this also rules out negative numbers
    if (candidate < 2) {
        return false;
    }

    // Handle 2, 3 as special cases
    // added the second "=" needed to compare the candidate value to the decimal value 2
    if (candidate == 2 || candidate == 3) {
        return true;
    }
    if (candidate % 2 == 0 || candidate % 3 == 0) {
        return false;
    }

    // Naive trial division
    //changed divisor from 5 to 3
    for (int divisor = 3, sqrt_candidate = static_cast<int>(std::sqrt(candidate));
        //changed divisor += from 6 to 2
         divisor < sqrt_candidate; divisor += 2) {
        //added == 0 after each condition
        if (candidate % divisor == 0 || candidate % (divisor + 2) == 0) {
            // Found a divisor
            return false;
        }
    }
    // Couldn't find a divisor, so it must be prime
    return true;
}

void test_is_prime() {

    std::vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
                               43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,
                               101, 103, 107, 109, 113, 127, 131, 137, 139,
                               149, 151, 157, 163, 167, 173, 179, 181, 191,
                               193, 197, 199};
//still not sure about the vector, the debug thingy isn't happy when I try to step through it but I don't know
//enough to know what it's doing. On the surface it looks fine because it builds and runs
    for (int i = 0, j = 0; i < 200; ++i) {
        if (i == primes[j]) {
            ++j;
            if (!is_prime(i)) {
                std::cout << "Error is_prime(" << i << ") was false\n";
            }
        } else {
            if (is_prime(i)) {
                std::cout << "Error is_prime(" << i << ") was true\n";
            }
        }
    }
}