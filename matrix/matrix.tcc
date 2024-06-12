#ifndef MATRIX_TCC
#define MATRIX_TCC

#include "matrix.h"
#include <cassert> // Für assert
#include <algorithm> // Für std::copy

template <class FLOAT, size_t N>
SquareMatrix<FLOAT, N>::SquareMatrix(std::initializer_list<Vector<FLOAT, N>> values) {
    assert(values.size() == N);
    std::copy(values.begin(), values.end(), matrix.begin());
}

template <class FLOAT, size_t N>
Vector<FLOAT, N> & SquareMatrix<FLOAT, N>::operator[](std::size_t i) {
    assert(i < N);
    return matrix[i];
}

template <class FLOAT, size_t N>
Vector<FLOAT, N> SquareMatrix<FLOAT, N>::operator[](std::size_t i) const {
    assert(i < N);
    return matrix[i];
}

template <class FLOAT, size_t N>
FLOAT SquareMatrix<FLOAT, N>::at(size_t row, size_t column) const {
    assert(row < N && column < N);
    return matrix[column][row];
}

template <class FLOAT, size_t N>
FLOAT & SquareMatrix<FLOAT, N>::at(size_t row, size_t column) {
    assert(row < N && column < N);
    return matrix[column][row];
}

template <class FLOAT, size_t N>
Vector<FLOAT, N> SquareMatrix<FLOAT, N>::operator*(const Vector<FLOAT, N> vector) {
    Vector<FLOAT, N> result;
    for (size_t i = 0; i < N; ++i) {
        result[i] = 0;
        for (size_t j = 0; j < N; ++j) {
            result[i] += this->at(i, j) * vector[j];
        }
    }
    return result;
}

template <class FLOAT, size_t N>
SquareMatrix<FLOAT, N> operator*(const SquareMatrix<FLOAT, N> factor1, const SquareMatrix<FLOAT, N> factor2) {
    SquareMatrix<FLOAT, N> result({});

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            result.at(i, j) = 0;
            for (size_t k = 0; k < N; ++k) {
                result.at(i, j) += factor1.at(i, k) * factor2.at(k, j);
            }
        }
    }

    return result;
}

#endif
