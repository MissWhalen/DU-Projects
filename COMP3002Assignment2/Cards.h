//
// Created by Briana on 1/27/2021.
//

#ifndef COMP3002ASSIGNMENT2_CARDS_H
#define COMP3002ASSIGNMENT2_CARDS_H
#include <iostream>


class Cards {
public:

    enum class Suits{
        Heart=0, Diamond, Club, Spade
    };
    enum class FaceValue{
         two = 2, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace
    };
    Cards(Suits a1, FaceValue a2);

    friend bool operator<(const Cards &lhs, const Cards &rhs);

    friend bool operator>(const Cards &lhs, const Cards &rhs);

    friend bool operator<=(const Cards &lhs, const Cards &rhs);

    friend bool operator>=(const Cards &lhs, const Cards &rhs);

    friend bool operator==(const Cards &lhs, const Cards &rhs);

    friend bool operator!=(const Cards &lhs, const Cards &rhs);

    friend std::ostream &operator<<(std::ostream &os, const Cards &cards);

    Suits getA1() const;

    void setA1(Suits a1);

    FaceValue getA2() const;

    void setA2(FaceValue a2);

private:
    Suits suits;
    FaceValue facevalue;


};



#endif //COMP3002ASSIGNMENT2_CARDS_H
