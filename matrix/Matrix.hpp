/**
 * @file Matrix.hpp
 *
 * A simple matrix template library.
 *
 * @author James Goppert <james.goppert@gmail.com>
 */

#pragma once

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Vector.hpp"

namespace matrix
{

template <typename Type, size_t M>
class Vector;

template<typename Type, size_t  M, size_t N>
class Matrix
{

protected:
    Type _data[M][N];

public:

    virtual ~Matrix() {};

    Matrix() :
        _data()
    {
    }

    Matrix(const Type *data) :
        _data()
    {
        memcpy(_data, data, sizeof(_data));
    }

    Matrix(const Matrix &other) :
        _data()
    {
        memcpy(_data, other._data, sizeof(_data));
    }

    /**
     * Accessors/ Assignment etc.
     */

    Type *data()
    {
        return _data[0];
    }

    inline Type operator()(size_t i, size_t j) const
    {
        return _data[i][j];
    }

    inline Type &operator()(size_t i, size_t j)
    {
        return _data[i][j];
    }

    /**
     * Matrix Operations
     */

    // this might use a lot of programming memory
    // since it instantiates a class for every
    // required mult pair, but it provides
    // compile time size_t checking
    template<size_t P>
    Matrix<Type, M, P> operator*(const Matrix<Type, N, P> &other) const
    {
        const Matrix<Type, M, N> &self = *this;
        Matrix<Type, M, P> res;
        res.setZero();

        for (size_t i = 0; i < M; i++) {
            for (size_t k = 0; k < P; k++) {
                for (size_t j = 0; j < N; j++) {
                    res(i, k) += self(i, j) * other(j, k);
                }
            }
        }

        return res;
    }

    Matrix<Type, M, N> operator+(const Matrix<Type, M, N> &other) const
    {
        Matrix<Type, M, N> res;
        const Matrix<Type, M, N> &self = *this;

        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                res(i , j) = self(i, j) + other(i, j);
            }
        }

        return res;
    }

    bool operator==(const Matrix<Type, M, N> &other) const
    {
        Matrix<Type, M, N> res;
        const Matrix<Type, M, N> &self = *this;

        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                if (self(i , j) != other(i, j)) {
                    return false;
                }
            }
        }

        return true;
    }

    Matrix<Type, M, N> operator-(const Matrix<Type, M, N> &other) const
    {
        Matrix<Type, M, N> res;
        const Matrix<Type, M, N> &self = *this;

        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                res(i , j) = self(i, j) - other(i, j);
            }
        }

        return res;
    }

    void operator+=(const Matrix<Type, M, N> &other)
    {
        Matrix<Type, M, N> &self = *this;
        self = self + other;
    }

    void operator-=(const Matrix<Type, M, N> &other)
    {
        Matrix<Type, M, N> &self = *this;
        self = self - other;
    }

    template<size_t P>
    void operator*=(const Matrix<Type, N, P> &other)
    {
        Matrix<Type, M, N> &self = *this;
        self = self * other;
    }

    /**
     * Scalar Operations
     */

    Matrix<Type, M, N> operator*(Type scalar) const
    {
        Matrix<Type, M, N> res;
        const Matrix<Type, M, N> &self = *this;

        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                res(i , j) = self(i, j) * scalar;
            }
        }

        return res;
    }

    Matrix<Type, M, N> operator+(Type scalar) const
    {
        Matrix<Type, M, N> res;
        const Matrix<Type, M, N> &self = *this;

        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                res(i , j) = self(i, j) + scalar;
            }
        }

        return res;
    }

    void operator*=(Type scalar)
    {
        Matrix<Type, M, N> &self = *this;

        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                self(i, j) = self(i, j) * scalar;
            }
        }
    }

    void operator/=(Type scalar)
    {
        Matrix<Type, M, N> &self = *this;
        self = self * (1.0f / scalar);
    }

    /**
     * Misc. Functions
     */

    void print()
    {
        Matrix<Type, M, N> &self = *this;
        printf("\n");

        for (size_t i = 0; i < M; i++) {
            printf("[");

            for (size_t j = 0; j < N; j++) {
                printf("%10g\t", double(self(i, j)));
            }

            printf("]\n");
        }
    }

    Matrix<Type, N, M> transpose() const
    {
        Matrix<Type, N, M> res;
        const Matrix<Type, M, N> &self = *this;

        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                res(j, i) = self(i, j);
            }
        }

        return res;
    }


    // tranpose alias
    inline Matrix<Type, N, M> T() const
    {
        return transpose();
    }

    void setZero()
    {
        memset(_data, 0, sizeof(_data));
    }

    void setIdentity()
    {
        setZero();
        Matrix<Type, M, N> &self = *this;

        for (size_t i = 0; i < M and i < N; i++) {
            self(i, i) = 1;
        }
    }

    inline void swapRows(size_t a, size_t b)
    {
        if (a == b) {
            return;
        }

        Matrix<Type, M, N> &self = *this;

        for (size_t j = 0; j < N; j++) {
            Type tmp = self(a, j);
            self(a, j) = self(b, j);
            self(b, j) = tmp;
        }
    }

    inline void swapCols(size_t a, size_t b)
    {
        if (a == b) {
            return;
        }

        Matrix<Type, M, N> &self = *this;

        for (size_t i = 0; i < M; i++) {
            Type tmp = self(i, a);
            self(i, a) = self(i, b);
            self(i, b) = tmp;
        }
    }

};

template<typename Type, size_t M, size_t N>
Matrix<Type, M, N> & zero() {
    Matrix<Type, M, N> m;
    m.setZero();
    return m;
}

typedef Matrix<float, 3, 3> Matrix3f;

}; // namespace matrix

/* vim: set et fenc=utf-8 ff=unix sts=0 sw=4 ts=4 : */