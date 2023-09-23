//
// Created by Briana on 4/12/2021.
//

#include "Fibonacci.h"
#include <stdexcept>

int fibonacci(int n) {
    if (n > 46 ){
        throw std::range_error("Out of range");
    }
    if (n < 0 ){
        throw std::invalid_argument("invalid argument");
    }
    if (n == 0) {
        return 0;
    }

    int fib_n = 1;
    int fib_nm1 = 1;
    int fib_nm2 = 1;
    for (int i = 1; i < n - 1; ++i) {
        fib_n = fib_nm1 + fib_nm2;
        fib_nm2 = fib_nm1;
        fib_nm1 = fib_n;
    }

    return fib_n;

}
