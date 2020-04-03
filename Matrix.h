//
// Created by Игорь Мельников on 03.04.2020.
//

#ifndef MATRIXES_MATRIX_H
#define MATRIXES_MATRIX_H

#include "BaseMatrix.cpp"
#include "Rational.cpp"
#include "compilation_control.cpp"

template <unsigned N, unsigned M, typename Field>
class Matrix {
public:
    BaseMatrix<Field> matrix_;
    explicit Matrix(bool = true);
    explicit Matrix(const BaseMatrix<Field>&);

    Matrix(std::initializer_list<std::initializer_list<Field>>);

    Matrix<N, M, Field>& operator+=(const Matrix<N, M, Field>&);
    Matrix<N, M, Field>& operator-=(const Matrix<N, M, Field>&);
    Matrix<N, M, Field>& operator*=(const Matrix<N, M, Field>&);
    Matrix<N, M, Field>& operator*=(const Field&);

    Matrix<N, M, Field> operator+(const Matrix<N, M, Field>&) const;
    Matrix<N, M, Field> operator-(const Matrix<N, M, Field>&) const;

    Matrix<N, M, Field> operator*(const Field&) const;

    template <unsigned K>
    Matrix<N, K, Field> operator*(const Matrix<M, K, Field>&) const;

    bool operator!=(const Matrix<N, M, Field>&) const;

    Matrix<M, N, Field> transposed() const;
    unsigned rank() const;

    void Dump() const;

    unsigned N_() const {return N;}
    unsigned M_() const {return M;}

    void Diagonalise();

    std::vector<Field>& operator[](unsigned);
    const std::vector<Field>& operator[](unsigned) const;

    Field det();
    Field trace();

    Matrix<N, M, Field> inverted();
    void invert();

    std::vector<Field> getRow(unsigned);
    std::vector<Field> getColumn(unsigned);
};


template <unsigned N, typename Field = Rational>
class SquareMatrix :  public Matrix<N, N, Field> {
public:
    explicit SquareMatrix(bool = true);
    explicit SquareMatrix(const BaseMatrix<Field>&);

    SquareMatrix(std::initializer_list<std::initializer_list<Field>>);
};

#endif //MATRIXES_MATRIX_H
