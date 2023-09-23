//
// Created by Briana on 2/10/2021.
//

#ifndef COMP3002MIDTERMQ1_MATRIX_H
#define COMP3002MIDTERMQ1_MATRIX_H


#include <ostream>

class Matrix {
public:
    int row, col;
    Matrix(int row, int col);
void draw_matrix(Matrix);

    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);

};


#endif //COMP3002MIDTERMQ1_MATRIX_H
