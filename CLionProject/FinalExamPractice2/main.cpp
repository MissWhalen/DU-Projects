#include <iostream>

int fun1(int x);

int fun2(int x, int y);

int main() {
    int x = fun1(42);
    std::cout << " x = " << x << " \n";
    int y = fun2(3, 5);
    std::cout << " y = " << y << " \n";
    return 0;
}

int fun1(int x) {
    if (x == 1) {
        return 1;
    }
    return 1 + fun1(x / 2);
}

int fun2(int x, int y) {
    if (y == 0) {
        return 0;
    }
    if (y % 2 == 0) {
        return fun2(x + x, y / 2);
    }
    return x + fun2(x + x, y / 2);
}