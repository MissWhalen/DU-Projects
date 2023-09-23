#include <iostream>
#include <cmath>

int main() {
    int n = 2;
    for (int i=2; i<n; i++)
        for (int j=2; j*j<=i; j++)
        {
            if (i % j == 0)
                break;
            else if (j+1 > sqrt(i)) {
                std::cout << i << std::endl;
            }
        }
    return 0;
}
