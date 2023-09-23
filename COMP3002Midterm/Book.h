//
// Created by Briana on 2/10/2021.
//

#ifndef COMP3002MIDTERM_BOOK_H
#define COMP3002MIDTERM_BOOK_H


#include <ostream>

class Book {
// rule of zero

    enum class book_info {
        title, author, copyrigth_year, ISBN


    };

public:
    Book(book_info);
    friend std::ostream &operator<<(std::ostream &os, const Book &book);
    void
};
#endif //COMP3002MIDTERM_BOOK_H
