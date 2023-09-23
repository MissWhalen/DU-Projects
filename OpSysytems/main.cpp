#include <iostream>


#include <algorithm>  // reverse
#include <vector>
int main() {
    std::vector<int> nums = {42, 32, 23, 51, 64};
    nums.push_back(89);
    for (int i=0; i<nums.size(); i++) std::cout << nums[i] << ' ';
    std::cout << '\n';
    reverse(nums.begin(), nums.end());
    for (int num: nums) std::cout << num << ' ';
    std::cout << '\n';
    int sum = 0;
    for (int num: nums) sum += num;
    std::cout << "Total and mean are " << sum << " and " << double(sum) / nums.size() << '\n';
    sort(nums.begin(), nums.end());
    for (int num: nums) std::cout << num << ' ';
    std::cout << '\n';

    std::vector<std::string> stooges = {"Larry", "Moe", "Christopher", "Curly"};
    reverse(stooges.begin(), stooges.end());
    for (int i=0; i<stooges.size(); i++) std::cout << stooges[i] << ' ';
    std::cout << '\n';

    // Note how to assign an array of std::strings to a std::vector
    // This did not work when applied to pro1b.cpp.
    std::string buff[] = {"Larry", "Moe", "Christopher", "Curly"};
    std::vector<std::string> names(begin(buff), end(buff));
    reverse(names.begin(), names.end());
    for (int i=0; i<names.size(); i++) std::cout << names[i] << ' ';
    std::cout << '\n';

    // Pushing and popping elements at the end of a std::vector
    std::vector<std::string> things = {"raindrops", "whiskers", "kettles"};
    // Appending an element
    things.push_back("mittens");
    things.push_back("packages");
    // Print it out
    for (std::string thing: things) std::cout << thing << ' ';
    std::cout << '\n';

    // Remove 3 elements from the end
    for (int i=0; i<3; i++) things.pop_back();
    // Print it out
    for (std::string thing: things) std::cout << thing << ' ';
    std::cout << '\n';

    return 0;
}

