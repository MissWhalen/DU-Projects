//Using C++17
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

int main(int argc, char *argv[]) {
    if (argc == 2) std::cout << "You have entered " << argc - 1 << " argument. \n";
    else std::cout << "You have entered " << argc - 1 << " arguments.\n";
    for (int i = 1; i < argc; i++) std::cout << argv[i] << "\n";
    std::string input_file = argv[1];


    if (argc == 1) {
        std::cout << "Incorrect input, you must enter the input text file." << "\n";
        return 1;
    }

    std::vector<std::string> text;
    std::string line;
    std::ifstream mytext(input_file);
    while (std::getline(mytext, line)) {
        //store the lines of text in a vector
        text.push_back(line);
    }
    mytext.close();
    //reverse the order of the lines in the vector
    std::reverse(text.begin(), text.end());

    std::string output_file;

    //if there is an output file name provided write out to that file
    if (argc == 3) {
        output_file = argv[2];
        std::ofstream out(output_file);
        for (const auto &i: text) {
            out << i << "\n";
        }
        out.close();
    }


    //if there is no file name provide write to std out
    if (argc == 2) {
        for (const auto &i: text) {
            std::cout << i << "\n";
        }
    }

    return 0;
    int MyClass::getMin(std::map<std::string, int> mymap) {
        std::pair<std::string, int> min = *min_element(mymap.begin(), mymap.end(),
                                                       &MyClass::compare);
        return min.second;
    }...
}
