//
// Created by Briana on 2/10/2021.
//

#include "Matrix.h"
#include <iostream>

Matrix::Matrix(int row, int col) {

}

void Matrix::draw_matrix(Matrix) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
        }
    }
    std::cout << "*";
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
    os << "row: " << matrix.row << " col: " << matrix.col;
    return os;
}
