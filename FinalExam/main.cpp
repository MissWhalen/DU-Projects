#include <iostream>

int calculate_TsubN(int n);

int main() {

    calculate_TsubN(50);
    return 0;
}

int calculate_TsubN(int n) {
    if (n == 0) {
        return 0;
    }
//I can't get this to work :(
    return calculate_TsubN(2 * (n - 1) + 1);

}