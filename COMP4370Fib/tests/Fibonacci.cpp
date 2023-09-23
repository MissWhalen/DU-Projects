//
// Created by Briana on 4/12/2021.
//

#include <gtest/gtest.h>
#include "../Fibonacci.h"

TEST(fibonacci, 10){
    int v = fibonacci(10);
    int expected = 55;
    EXPECT_EQ(v, expected);
}

TEST(fibonacci, 45){
int v = fibonacci(45);
int expected = 1134903170;
EXPECT_EQ(v, expected);
}
TEST(fibonacci, 46){
    int v = fibonacci(46);
    int expected = 1836311903;
    EXPECT_EQ(v, expected);
}

TEST(fibonacci, 0){
    int v = fibonacci(0);
    int expected = 0;
    EXPECT_EQ(v, expected);
}
TEST(fibonacci, 1){
    int v = fibonacci(1);
    int expected = 1;
    EXPECT_EQ(v, expected);
}
TEST(fibonacci, 2){
    int v = fibonacci(2);
    int expected = 1;
    EXPECT_EQ(v, expected);
}

TEST(fibonocci, too_big){
    EXPECT_THROW(fibonacci(47),std::range_error);

}

TEST(fibonocci, negative){
    EXPECT_THROW(fibonacci(-1), std::invalid_argument);
}
