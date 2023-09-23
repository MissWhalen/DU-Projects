#include <iostream>
#include "Fibonacci.h"
#include "MergeSort.h"
#include "Vectors.h"

int main() {
    auto rando = random_numbers();
    std::cout << "The 40th Fibonacci number is " << fibonacci(40) << "\n";
    std::cout << "\n";
    std::cout << "Ten random integers: " << "\n";
    print(rando);
    std::cout << "\n";
    std::cout << "Sorted integers: " << "\n";
    merge_sort(rando, 0,rando.size()-1);
    print(rando);
    std::cout << "\n";
    std::cout << "Unsorted vector of strings: " << "\n";
    std::vector<std::string> strings{"red", "yellow", "blue", "green", "purple", "pink", "black", "orange", "brown",
                                     "magenta", "chartreuse"};
    print(strings);
    std::cout << "\n";
    std::cout << "Sorted vector of string: " << "\n";
    merge_sort(strings, 0, strings.size()-1);
    print(strings);

    return 0;
}
