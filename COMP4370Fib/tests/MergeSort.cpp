//
// Created by Briana on 4/12/2021.
//
#include <gtest/gtest.h>
#include "../MergeSort.h"
#include <string>

TEST(Merge, Simple1324) {
    std::vector<int> v{1, 3, 2, 4};
    std::vector<int> expected{1, 2, 3, 4};
    merge(v, 0, 1, 3);

    EXPECT_EQ(v, expected);
}

TEST(Merge, Simple132) {
    std::vector<int> v{1, 3, 2};
    std::vector<int> expected{1, 2, 3};
    merge(v, 0, 1, 2);

    EXPECT_EQ(v, expected);
}

TEST(MergeSort, integers) {
    std::vector<int> v{1, 5, 2, 4, 3};
    std::vector<int> expected{1, 2, 3, 4, 5};
    merge_sort(v, 0, 4);

    EXPECT_EQ(v, expected);

}

TEST(MergeSort, strings) {
    std::vector<std::string> v{"banana", "apple", "pear", "melon"};
    std::vector<std::string> expected{"apple", "banana", "melon", "pear"};
    merge_sort(v, 0,v.size()-1);

    EXPECT_EQ(v, expected);

}

TEST(MergeSort, letters) {
std::vector<std::string> v{"aaa", "ccc", "bbb", "ddd"};
std::vector<std::string> expected{"aaa", "bbb", "ccc", "ddd"};
merge_sort(v, 0,v.size()-1);

EXPECT_EQ(v, expected);

}