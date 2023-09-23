#include <iostream>

#include<string>
#include <algorithm>

bool permutations(std::string a, std::string b);


int main() {


    std::string a = "abcd";
    std::string b = "acdb";
    permutations(a,b);
    std::string c = "abcgdn";
    std::string d = "avcbdb";
    permutations(c,d);
    return 0;
}

bool permutations(std::string a, std::string b) {

    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    if (a == b) {

        std::cout << "String " << a << " is are permutation of sting " << b << "\n";
        return true;
    }else{
        std::cout << "These strings are not permutations of one another\n";
        return false;
    }

}


