//
// Created by Игорь Мельников on 03.04.2020.
//

#ifndef MATRIXES_BIGINEGER_H
#define MATRIXES_BIGINEGER_H

#include <iostream>
#include <vector>

class BigInteger {
public:
    BigInteger();

    BigInteger(long long int);

    bool operator>(const BigInteger&) const;
    bool operator>(int) const;
    bool operator>=(const BigInteger&) const;
    bool operator>=(int) const;
    bool operator<(const BigInteger&) const;
    bool operator<(int) const;
    bool operator<=(const BigInteger&) const;

    bool operator!=(const BigInteger&) const;
    bool operator==(const BigInteger&) const;
    bool operator==(int) const;

    BigInteger& operator+=(const BigInteger&);
    BigInteger& operator-=(const BigInteger&);
    BigInteger& operator*=(const BigInteger&);
    BigInteger& operator/=(const BigInteger&);

    BigInteger operator+(const BigInteger&) const;
    BigInteger operator-(const BigInteger&) const;
    BigInteger operator*(const BigInteger&) const;
    BigInteger operator/(const BigInteger&) const;
    BigInteger operator%(const BigInteger&) const;

    BigInteger& operator*=(const int&);
    BigInteger operator*(const int&) const;

    BigInteger operator-() const;

    BigInteger QuickNOD(const BigInteger&) const;

    BigInteger& Quick_divide_by_2();

    void fromString(std::string);
    std::string toString() const;

    BigInteger abs() const;


    void Dump() const ;

    size_t size();

    static const long int Base = 10000;
    static const int Deg = 4;

    BigInteger pow(size_t);

private:
    std::vector<long int> array_;
    bool sign;



    void move_normal_digits();
    void make_array_positive();

    bool abs_more(const BigInteger& other) const;
};

int find(const BigInteger& a, const BigInteger& b);

#endif //MATRIXES_BIGINEGER_H
