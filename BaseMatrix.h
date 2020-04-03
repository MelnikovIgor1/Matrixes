//
// Created by Игорь Мельников on 03.04.2020.
//

#ifndef MATRIXES_BASEMATRIX_H
#define MATRIXES_BASEMATRIX_H

#include <iostream>

template <typename Field>
class BaseMatrix {
public:
    BaseMatrix(unsigned, unsigned, bool = false);
    BaseMatrix(std::initializer_list<std::initializer_list<Field>>);

    BaseMatrix<Field>& operator+=(const BaseMatrix<Field>&);
    BaseMatrix<Field>& operator-=(const BaseMatrix<Field>&);
    BaseMatrix<Field>& operator*=(const BaseMatrix<Field>&);
    BaseMatrix<Field>& operator*=(const Field&);

    BaseMatrix<Field> operator+(const BaseMatrix<Field>&) const;
    BaseMatrix<Field> operator-(const BaseMatrix<Field>&) const;

    BaseMatrix<Field> operator*(const Field&) const;

    template <typename T>
    friend BaseMatrix<T> operator*(const T&, const BaseMatrix<T>&);
    BaseMatrix<Field> operator*(const BaseMatrix&) const;

    bool operator!=(const BaseMatrix<Field>&) const;

    Field det() const;
    BaseMatrix<Field> transposed() const;
    unsigned rank() const;
    Field trace() const;

    void Dump() const;

    unsigned N() const {return N_;}
    unsigned M() const {return M_;}

    unsigned Diagonalise();

    std::vector<Field>& operator[](unsigned);
    const std::vector<Field>& operator[](unsigned) const;

    BaseMatrix<Field> inverted() const;
    void invert();

    static BaseMatrix<Field> One(unsigned);

    std::vector<Field> getRow(unsigned) const;
    std::vector<Field> getColumn(unsigned) const;

    void copy_in(std::pair<unsigned, unsigned>, const BaseMatrix&);

private:
    std::vector<std::vector<Field>> array_;

    unsigned N_;
    unsigned M_;

    BaseMatrix<Field> SubMatrix(unsigned, unsigned, unsigned, unsigned) const;

    void SwapLines_(unsigned, unsigned);
    void SubtractLines_(unsigned, unsigned, Field);

    std::vector<BaseMatrix<Field>> Split() const;
    std::vector<BaseMatrix<Field>> otherSplit() const;


    BaseMatrix<Field> Expanded_matrix(std::pair<unsigned, unsigned>) const;
    BaseMatrix<Field> multiply_if_degree_of_2(const BaseMatrix&) const;
    BaseMatrix<Field> QuickMultiply(const BaseMatrix<Field>& matrix) const;
};

unsigned lower_2_degree(unsigned);

template <typename Field>
BaseMatrix<Field> Combine(const std::vector<BaseMatrix<Field>>&);



#endif //MATRIXES_BASEMATRIX_H
