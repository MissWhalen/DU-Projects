//Brian Whalen
//Bridge Course: C and C++
//Assigment 1: Age Calculations

#include <iostream>

int main() {
    std::cout << "How old are you in years?" << std::endl;
    int value;
    std::cin >> value; // value will represent the age of the person
    std::cout << "You have been alive for: " << std::endl; // prompts user for input
    std::cout << value * 12 << " Months" << std::endl;
    std::cout << (value / 4) + value * 365 << " Days" << std::endl;
    int a = (value / 4) + (value * 365); // a will now represent days to make further calculations easier
    std::cout << (a * 24) * 60 << " Minutes" << std::endl;
    long long b = (a * 24) * 60; // b will now represent minutes for further calculations
    std::cout << b * 60 << " Seconds" << std::endl;
    long long c = b * 60; // c will now represent seconds
    double d = c * 1000;// d will represent milliseconds
    std::cout << d << " Milliseconds" << std::endl;

    std::cout << value * 7 << " Dog Years" << std::endl;



    return 0;
}
