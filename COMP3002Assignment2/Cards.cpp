//
// Created by Briana on 1/27/2021.
//

#include "Cards.h"


Cards::Suits Cards::getA1() const {
    return suits;
}

Cards::FaceValue Cards::getA2() const {
    return facevalue;
}

void Cards::setA1(Cards::Suits a1_) {
    Cards::suits = a1_;
}

void Cards::setA2(Cards::FaceValue a2_) {
    Cards::facevalue = a2_;
}
// Setting up Cards
std::ostream &operator<<(std::ostream &os, const Cards &cards) {
    os << "Suit ";
    switch (cards.suits){
        case Cards::Suits::Heart:
            os << "Heart";
            break;
        case Cards::Suits::Club:
            os << "Club";
            break;
        case Cards::Suits::Spade:
            os << "Spade";
            break;
        case Cards::Suits::Diamond:
            os << "Diamond";
            break;
    }
    os << "Face Value ";
    switch(cards.facevalue){

        case Cards::FaceValue::two:
        case Cards::FaceValue::three:
        case Cards::FaceValue::four:
        case Cards::FaceValue::five:
        case Cards::FaceValue::six:
        case Cards::FaceValue::seven:
        case Cards::FaceValue::eight:
        case Cards::FaceValue::nine:
        case Cards::FaceValue::ten:
            os << static_cast<int>(cards.facevalue);
            break;
        case Cards::FaceValue::jack:
            os << "jack";
            break;
        case Cards::FaceValue::queen:
            os << "queen";
            break;
        case Cards::FaceValue::king:
            os << "king";
            break;
        case Cards::FaceValue::ace:
            os << "ace";

            break;
    }
    return os;
}

Cards::Cards(Cards::Suits a1_, Cards::FaceValue a2_) : suits(a1_), facevalue(a2_) {

}

bool operator==(const Cards &lhs, const Cards &rhs) {
    return lhs.facevalue == rhs.facevalue;
}

bool operator!=(const Cards &lhs, const Cards &rhs) {
    return !(rhs == lhs);
}

bool operator<(const Cards &lhs, const Cards &rhs) {
    return lhs.facevalue < rhs.facevalue;
}

bool operator>(const Cards &lhs, const Cards &rhs) {
    return rhs < lhs;
}

bool operator<=(const Cards &lhs, const Cards &rhs) {
    return !(rhs < lhs);
}

bool operator>=(const Cards &lhs, const Cards &rhs) {
    return !(lhs < rhs);
}
