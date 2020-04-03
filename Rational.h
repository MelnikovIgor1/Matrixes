//
// Created by Игорь Мельников on 03.04.2020.
//

#ifndef MATRIXES_RATIONAL_H
#define MATRIXES_RATIONAL_H

#include "BigIneger.cpp"

class Rational
{
public:
    Rational();
    Rational(const int);
    Rational(const BigInteger&);
    Rational(const BigInteger&, const BigInteger&);

    Rational operator-();

    Rational& operator+=(const Rational& x);
    Rational& operator-=(const Rational& x);
    Rational& operator*=(const Rational& x);
    Rational& operator/=(const Rational& x);

    friend Rational operator+(const Rational& a, const Rational& b);
    friend Rational operator-(const Rational& a, const Rational& b);
    friend Rational operator*(const Rational& a, const Rational& b);
    friend Rational operator/(const Rational& a, const Rational& b);

    friend bool operator==(const Rational&, const Rational&);
    friend bool operator!=(const Rational&, const Rational&);
    friend bool operator>=(const Rational&, const Rational&);
    friend bool operator<=(const Rational&, const Rational&);
    friend bool operator< (const Rational&, const Rational&);
    friend bool operator> (const Rational&, const Rational&);

    std::string toString() const;
    std::string asDecimal(size_t precision=0) const;

    operator double() const;

    Rational abs() const;

private:
    BigInteger numerator_;
    BigInteger denominator_;

    void Simplify_();
};

#endif //MATRIXES_RATIONAL_H
