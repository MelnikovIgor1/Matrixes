//
// Created by Игорь Мельников on 03.04.2020.
//

#include "Finite.h"

template <unsigned Module>
Finite<Module> Finite<Module>::operator -() {
    return *this * Finite<Module>(-1);
}

template <unsigned Module>
Finite<Module>::Finite(int x) :
        value((x >= 0)? x%Module : Module -(-x)%Module) {

}

template<unsigned Module>
Finite<Module>::Finite(unsigned x) :
        value(x%Module) {

}

template<unsigned int Module>
Finite<Module> Finite<Module>::operator +(const Finite<Module>& x) const {
    return Finite<Module>(x.value + value);
}

template<unsigned int Module>
Finite<Module> Finite<Module>::operator -(const Finite<Module>& x) const {
    return Finite<Module>(-x.value + value);
}

template<unsigned int Module>
Finite<Module> Finite<Module>::operator *(const Finite<Module>& x) const {
    return Finite<Module>(x.value * value);
}

template<unsigned int Module>
Finite<Module> Finite<Module>::operator /(const Finite<Module>& x) const {
    if (!(is_prime<Module>::result+1)) std::cout << "Hio";
    return Finite<Module>(x.reverse().value * value);
}

template<unsigned int Module>
Finite<Module> Finite<Module>::reverse() const {
    LRGCD x(value, Module);

    return Finite<Module>(x.Coefficients().first);
}

template<unsigned int Module>
void Finite<Module>::Dump() const {
    std::cout << value;
}

template <unsigned Module>
Finite<Module>::Finite() :
        value(0) {
}

template<unsigned int Module>
bool Finite<Module>::operator ==(const Finite<Module>& x) const {
    return value == x.value;
}

template<unsigned int Module>
bool Finite<Module>::operator !=(const Finite<Module>& x) const {
    return value != x.value;
}

template<unsigned int Module>
Finite<Module>& Finite<Module>::operator -=(const Finite<Module>& x)
{
    *this = *this - x;
    return *this;
}

template<unsigned int Module>
Finite<Module> &Finite<Module>::operator /=(const Finite<Module>& x) {
    *this = *this / x;
    return *this;
}

template<unsigned int Module>
Finite<Module> &Finite<Module>::operator +=(const Finite<Module>& x) {
    *this = *this + x;
    return *this;
}

template<unsigned int Module>
Finite<Module> &Finite<Module>::operator *=(const Finite<Module>& x) {
    *this = (*this) * x;
    return *this;
}

template<unsigned int Module>
Finite<Module> &Finite<Module>::operator ++() {
    *this += 1;

    return *this;
}

template<unsigned int Module>
Finite<Module> &Finite<Module>::operator --() {
    *this -= 1;

    return *this;
}

template<unsigned int Module>
Finite<Module> Finite<Module>::operator ++(int) {
    auto answer = *this;
    *this += 1;

    return answer;
}

template<unsigned int Module>
Finite<Module> Finite<Module>::operator--(int) {
    auto answer = *this;
    *this -= 1;

    return answer;
}

void LRGCD::DoTheMath_() {
    if (a_ == 0) {
        a_coefficient_ = 0;
        b_coefficient_ = b_sign_;

        return;
    }

    if (b_ == 0) {
        a_coefficient_ = a_sign_;
        b_coefficient_ = 0;

        return;
    }

    if (a_ >= b_) {
        LRGCD x = LRGCD(a_ % b_, b_);

        a_coefficient_ = x.a_coefficient_;
        b_coefficient_ = x.b_coefficient_ -(a_/b_)*x.a_coefficient_;

        a_coefficient_ *= a_sign_;
        b_coefficient_ *= b_sign_;

        return;
    } else {
        LRGCD x = LRGCD(a_, b_%a_);

        a_coefficient_ = x.a_coefficient_ -(b_/a_)*x.b_coefficient_;
        b_coefficient_ = x.b_coefficient_;

        a_coefficient_ *= a_sign_;
        b_coefficient_ *= b_sign_;

        return;
    }
}

LRGCD::LRGCD(int a, int b) :
        a_(abs(a)),
        b_(abs(b)),
        a_sign_((a >= 0)? 1 : -1),
        b_sign_((b >= 0)? 1 : -1),
        a_coefficient_(0),
        b_coefficient_(0)
{
    DoTheMath_();
}

std::pair<int, int> LRGCD::Coefficients()
{
    return std::pair<int, int>(a_coefficient_, b_coefficient_);
}