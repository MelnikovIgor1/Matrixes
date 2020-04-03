//
// Created by Игорь Мельников on 03.04.2020.
//

#ifndef MATRIXES_FINITE_H
#define MATRIXES_FINITE_H


class LRGCD {
public:
    LRGCD(int, int);

    std::pair<int, int> Coefficients();

private:
    unsigned a_;
    unsigned b_;

    int a_sign_;
    int b_sign_;

    int a_coefficient_;
    int b_coefficient_;

    void DoTheMath_();
};

template <unsigned Module>
class Finite
{
public:
    Finite(int x);
    Finite(unsigned x);
    Finite();

    Finite<Module>operator+(const Finite<Module>&) const;
    Finite<Module>operator-(const Finite<Module>&) const;
    Finite<Module>operator*(const Finite<Module>&) const;
    Finite<Module>operator/(const Finite<Module>&) const;

    Finite<Module>&operator+=(const Finite<Module>&);
    Finite<Module>&operator-=(const Finite<Module>&);
    Finite<Module>&operator*=(const Finite<Module>&);
    Finite<Module>&operator/=(const Finite<Module>&);

    Finite<Module>&operator++();
    Finite<Module>&operator--();

    Finite<Module>operator++(int);
    Finite<Module>operator--(int);

    Finite<Module>operator-();

    booloperator!=(const Finite<Module>&) const;
    booloperator==(const Finite<Module>&) const;

    Finite<Module> pow(unsigned);

    Finite<Module> reverse() const;

    void Dump() const;

private:
    int value;
};


std::pair<int, int> NOD(std::pair<int, int> value, std::pair<int, int> coefficients);


#endif //MATRIXES_FINITE_H
