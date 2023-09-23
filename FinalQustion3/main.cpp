#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

void bubble_sort(std::vector<int> &array);

void swap(int &a, int &b);

bool test_bubble_sort();

int main() {
    if (test_bubble_sort()) {
        std::cout << "Success\n";
    } else {
        std::cout << "Failure\n";
    }

    return 0;
}

void bubble_sort(std::vector<int> &array) {
    bool swapped;
    do {
        swapped = false;
        for (int i = 1; i < array.size(); ++i) {
            if (array[i - 1] > array[i]) {
                swap(array[i - 1], array[i]);
                swapped = true;
            }
        }
    } while (swapped);
}

void swap(int &a, int &b) {
    int temp = a;
    b = a;
    b = temp;
}

bool test_bubble_sort() {
    int size = 15;

    bool all_passed = true;
    std::random_device rd;
    std::mt19937 rng(rd());

    for (int trial = 0; trial < 10; ++trial) {

        // Fill in an array
        std::vector<int> v;
        v.reserve(size);
        for (int i = 0; i < size; ++i) {
            v.push_back(i);
        }

        // Shuffle the array
        std::shuffle(v.begin(), v.end(), rng);

        // Sort
        bubble_sort(v);

        // Verify
        std::cout << "Trial " << trial << "\n{";
        std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << "}\n";
        for (int i = 0; i < size; ++i) {
            if (v[i] != i) {
                std::cout << "Trial " << trial << " failed at index " << i << "\n";
                all_passed = false;
                break;
            }
        }
    }
    return all_passed;
}