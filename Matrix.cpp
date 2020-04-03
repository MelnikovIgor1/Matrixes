//
// Created by Игорь Мельников on 03.04.2020.
//

#include "Matrix.h"


template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field>::Matrix(bool par) :
        matrix_(N, M, par) {
    is_field<Field>::check();
}

template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field> &Matrix<N, M, Field>::operator+=(const Matrix<N, M, Field>& x) {
    matrix_ += x.matrix_;

    return *this;
}

template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field>::Matrix(const BaseMatrix<Field> & par) :
        matrix_ (par) {
    is_field<Field>::check();
}

template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field> &Matrix<N, M, Field>::operator-=(const Matrix<N, M, Field>& x) {
    matrix_ -= x.matrix_;

    return *this;
}

template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field> Matrix<N, M, Field>::operator+(const Matrix<N, M, Field>& x) const {
    return Matrix<N, M, Field>(matrix_ + x.matrix_);
}

template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field> Matrix<N, M, Field>::operator-(const Matrix<N, M, Field>& x) const {
    return Matrix<N, M, Field>(matrix_ - x.matrix_);
}

template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field> Matrix<N, M, Field>::operator*(const Field& k) const {
    return Matrix<N, M, Field>(matrix_ * k);
}

template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field> operator*(Field k, const Matrix<N, M, Field>& m) {
    return Matrix<N, M, Field>(m * k);
}

template<unsigned int N, unsigned int M, typename Field>
template <unsigned K>
Matrix<N, K, Field> Matrix<N, M, Field>::operator*(const Matrix<M, K, Field>& m) const {
    return Matrix<N, K, Field>(matrix_ * m.matrix_);
}

template<unsigned int N, unsigned int M, typename Field>
Matrix<M, N, Field> Matrix<N, M, Field>::transposed() const {
    return Matrix<M, N, Field>(matrix_.transposed());
}

template<unsigned int N, unsigned int M, typename Field>
unsigned Matrix<N, M, Field>::rank() const {
    return matrix_.rank();
}

template<unsigned int N, unsigned int M, typename Field>
void Matrix<N, M, Field>::Dump() const {
    matrix_.Dump();
}

template<unsigned int N, unsigned int M, typename Field>
void Matrix<N, M, Field>::Diagonalise() {
    matrix_.Diagonalise();
}

template<unsigned int N, unsigned int M, typename Field>
std::vector<Field> &Matrix<N, M, Field>::operator[](unsigned i) {
    return matrix_[i];
}

template<unsigned int N, unsigned int M, typename Field>
const std::vector<Field> &Matrix<N, M, Field>::operator[](unsigned i) const {
    return matrix_[i];
}

template<unsigned int N, unsigned int M, typename Field>
std::vector<Field> Matrix<N, M, Field>::getRow(unsigned i) {
    return matrix_.getRow(i);
}

template<unsigned int N, unsigned int M, typename Field>
std::vector<Field> Matrix<N, M, Field>::getColumn(unsigned i) {
    return matrix_.getColumn(i);
}

template<unsigned int N, unsigned int M, typename Field>
Field Matrix<N, M, Field>::trace() {
    are_equal<N, M>::do_nothing();
    return matrix_.trace();
}

template<unsigned int N, unsigned int M, typename Field>
Field Matrix<N, M, Field>::det() {
    are_equal<N, M>::do_nothing();
    return matrix_.det();
}

template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field> Matrix<N, M, Field>::inverted() {
    are_equal<N, M>::do_nothing();
    return Matrix<N, M, Field>(matrix_.inverted());
}

template<unsigned int N, unsigned int M, typename Field>
void Matrix<N, M, Field>::invert() {
    are_equal<N, M>::do_nothing();

    matrix_.invert();
}

template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field>::Matrix(std::initializer_list<std::initializer_list<Field>> list) :
        matrix_(list) {

}

template<unsigned int N, unsigned int M, typename Field>
bool Matrix<N, M, Field>::operator!=(const Matrix<N, M, Field>& matrix) const {
    return matrix_ != matrix.matrix_;
}

template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field> &Matrix<N, M, Field>::operator*=(const Matrix<N, M, Field>& other) {
    matrix_ *= other.matrix_;

    return *this;
}

template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field> &Matrix<N, M, Field>::operator*=(const Field& f) {
    matrix_ *= f;

    return *this;
}

template<unsigned int N, typename Field>
SquareMatrix<N, Field>::SquareMatrix(std::initializer_list<std::initializer_list<Field>> list):
        Matrix<N, N, Field>(list) {

}

template<unsigned int N, typename Field>
SquareMatrix<N, Field>::SquareMatrix(const BaseMatrix<Field>& matrix):
        Matrix<N, N, Field>(matrix) {

}

template<unsigned int N, typename Field>
SquareMatrix<N, Field>::SquareMatrix(bool boolean):
        Matrix<N, N, Field>(boolean) {

}