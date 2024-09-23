#include "Matrix.h"

#include <iostream>
#include <stdexcept>

Matrix::Matrix(unsigned rows, unsigned columns, float itemValue)
: mRows(rows)
, mColumns(columns) {
    if(mRows == 0 || mColumns == 0) {
        throw std::invalid_argument("Matrix sizes should be grater than 0");
    }

    mData = new float[mRows * mColumns];
    std::fill(mData, mData + mRows * mColumns, itemValue);
}

Matrix::Matrix(const Matrix& another)
: mRows(another.mRows)
, mColumns(another.mColumns) {
    mData = new float[mRows * mColumns];
    std::copy(another.mData, another.mData + mRows * mColumns, mData);
}

Matrix::Matrix(unsigned rows, unsigned columns, std::initializer_list<float> values)
: mRows(rows)
, mColumns(columns) {
    if (mRows == 0 || mColumns == 0) {
        throw std::invalid_argument("Matrix sizes should be grater than 0");
    }

    if (mRows * mColumns != values.size()) {
        throw std::invalid_argument("Matrix size doesn't correspond to size of initializer list");
    }

    mData = new float[mRows * mColumns];
    std::copy(values.begin(), values.end(), mData);
}

Matrix::~Matrix() {
    if(mData) {
        delete [] mData;
        mData = nullptr;
    }
}

std::pair<unsigned, unsigned> Matrix::GetSize() const {
    return {mRows, mColumns};
}

float& Matrix::operator()(unsigned i, unsigned j) {
    return mData[i * mColumns + j];
}

const float& Matrix::operator()(unsigned i, unsigned j) const {
    return mData[i * mColumns + j];
}

Matrix& Matrix::operator+=(const Matrix& another) {
    if(mRows != another.mRows || mColumns != another.mColumns) {
        throw std::invalid_argument("Matrices should have the same size");
    }

    for(unsigned idx = 0; idx < mRows*mColumns; ++idx) {
        *(mData + idx) += *(another.mData + idx);
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& another) {
    if(mRows != another.mRows || mColumns != another.mColumns) {
        throw std::invalid_argument("Matrices should have the same size");
    }

    for(unsigned idx = 0; idx < mRows*mColumns; ++idx) {
        *(mData + idx) -= *(another.mData + idx);
    }
    return *this;
}

Matrix& Matrix::operator*=(float scalar) {
    for(unsigned idx = 0; idx < mRows*mColumns; ++idx) {
        *(mData + idx) *= scalar;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    os << "Matrix size: (" << matrix.mRows << "; " << matrix.mColumns << ")" << std::endl;
    for(unsigned i = 0; i < matrix.mRows; ++i) {
        os << "[ ";
        for(unsigned j = 0; j < matrix.mColumns; ++j) {
            os << matrix(i, j) << " ";
        }
        os << "]" << std::endl;
    }

    return os;
}