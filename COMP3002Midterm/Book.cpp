//
// Created by Briana on 2/10/2021.
//

#include "Book.h"
#include <iostream>



std::ostream &operator<<(std::ostream &os, const Book &book) {
    os << "Book 1: ";
    os << Book::book_info::title;
    os << Book::book_info::author;
    os << Book::book_info::copyrigth_year;
    os << Book::book_info::ISBN;


    return os;
}


Book::Book(book_info) {

}




