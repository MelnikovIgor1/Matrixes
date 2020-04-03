//
// Created by Игорь Мельников on 03.04.2020.
//

#include "Rational.h"


Rational::Rational() :
        numerator_(),
        denominator_()
{

}

Rational::Rational(int n) :
        numerator_(n),
        denominator_(1)
{

}

Rational::Rational(const BigInteger& x) :
        numerator_(x),
        denominator_(1)
{

}

Rational::Rational(const BigInteger& x, const BigInteger& y) :
        numerator_(x),
        denominator_(y)
{

}

void Rational::Simplify_()
{
    BigInteger a = numerator_.abs();
    BigInteger b = denominator_.abs();

    if (a == 0)
    {
        denominator_ = BigInteger(1);
        return;
    }

    BigInteger NOD_ = NOD(a, b);

    if (denominator_ < 0)
    {
        denominator_ = denominator_.abs();
        numerator_ = -numerator_;
    }

    numerator_ /= NOD_;
    denominator_ /= NOD_;
}

Rational Rational::operator-()
{
    Rational answer;
    answer = *this;

    answer.numerator_ = -answer.numerator_;

    return answer;
}

Rational& Rational::operator+=(const Rational& x)
{
    (numerator_ *= x.denominator_) += x.numerator_ * denominator_;
    denominator_ *= x.denominator_;

    Simplify_();

    return *this;
}
Rational& Rational::operator-=(const Rational& x)
{
   (numerator_ *= x.denominator_) -= x.numerator_ * denominator_;
    denominator_ *= x.denominator_;

    Simplify_();

    return *this;
}
Rational& Rational::operator*=(const Rational& x)
{
    numerator_ *= x.numerator_;
    denominator_ *= x.denominator_;

    Simplify_();

    return *this;
}
Rational& Rational::operator/=(const Rational& x)
{
    numerator_ *= x.denominator_;
    denominator_ *= x.numerator_;

    if (denominator_ < 0)
    {
        denominator_ = -denominator_;
        numerator_ = -numerator_;
    }

    Simplify_();

    return *this;
}

Rational operator+(const Rational& a, const Rational& b)
{
    Rational answer = a;

    answer += b;

    return answer;
}
Rational operator-(const Rational& a, const Rational& b)
{
    Rational answer = a;

    answer -= b;

    return answer;
}
Rational operator*(const Rational& a, const Rational& b)
{
    Rational answer = a;

    answer *= b;

    return answer;
}
Rational operator/(const Rational& a, const Rational& b)
{
    Rational answer = a;

    answer /= b;

    return answer;
}

bool operator==(const Rational& a, const Rational& b)
{
    if (a.numerator_ == 0 && b.numerator_ == 0) return true;
    return (a.numerator_ == b.numerator_ && a.denominator_ == b.denominator_);
}
bool operator!=(const Rational& a, const Rational& b)
{
    return !(a == b);
}
bool operator>=(const Rational& a, const Rational& b)
{
    return  (a > b) || (a == b);
}
bool operator<=(const Rational& a, const Rational& b)
{
    return (a < b) || (a == b);
}
bool operator< (const Rational& a, const Rational& b)
{
    return b > a;
}
bool operator> (const Rational& a, const Rational& b)
{
    return (a.numerator_ * b.denominator_ > b.numerator_ * a.denominator_);
}

bool operator==(int a, const Rational& b) {return static_cast<Rational>(a) == static_cast<Rational>(b);}
bool operator!=(int a, const Rational& b) {return static_cast<Rational>(a) != static_cast<Rational>(b);}
bool operator>=(int a, const Rational& b) {return static_cast<Rational>(a) >= static_cast<Rational>(b);}
bool operator<=(int a, const Rational& b) {return static_cast<Rational>(a) <= static_cast<Rational>(b);}
bool operator< (int a, const Rational& b) {return static_cast<Rational>(a) <  static_cast<Rational>(b);}
bool operator> (int a, const Rational& b) {return static_cast<Rational>(a) >  static_cast<Rational>(b);}

bool operator==(const Rational& a, int b) {return static_cast<Rational>(a) == static_cast<Rational>(b);}
bool operator!=(const Rational& a, int b) {return static_cast<Rational>(a) != static_cast<Rational>(b);}
bool operator>=(const Rational& a, int b) {return static_cast<Rational>(a) >= static_cast<Rational>(b);}
bool operator<=(const Rational& a, int b) {return static_cast<Rational>(a) <= static_cast<Rational>(b);}
bool operator< (const Rational& a, int b) {return static_cast<Rational>(a) <  static_cast<Rational>(b);}
bool operator> (const Rational& a, int b) {return static_cast<Rational>(a) >  static_cast<Rational>(b);}

bool operator==(const BigInteger& a, const Rational& b) {return static_cast<Rational>(a) == static_cast<Rational>(b);}
bool operator!=(const BigInteger& a, const Rational& b) {return static_cast<Rational>(a) != static_cast<Rational>(b);}
bool operator>=(const BigInteger& a, const Rational& b) {return static_cast<Rational>(a) >= static_cast<Rational>(b);}
bool operator<=(const BigInteger& a, const Rational& b) {return static_cast<Rational>(a) <= static_cast<Rational>(b);}
bool operator< (const BigInteger& a, const Rational& b) {return static_cast<Rational>(a) <  static_cast<Rational>(b);}
bool operator> (const BigInteger& a, const Rational& b) {return static_cast<Rational>(a) >  static_cast<Rational>(b);}

bool operator==(const Rational& a, const BigInteger& b) {return static_cast<Rational>(a) == static_cast<Rational>(b);}
bool operator!=(const Rational& a, const BigInteger& b) {return static_cast<Rational>(a) != static_cast<Rational>(b);}
bool operator>=(const Rational& a, const BigInteger& b) {return static_cast<Rational>(a) >= static_cast<Rational>(b);}
bool operator<=(const Rational& a, const BigInteger& b) {return static_cast<Rational>(a) <= static_cast<Rational>(b);}
bool operator< (const Rational& a, const BigInteger& b) {return static_cast<Rational>(a) <  static_cast<Rational>(b);}
bool operator> (const Rational& a, const BigInteger& b) {return static_cast<Rational>(a) >  static_cast<Rational>(b);}

Rational operator+(int a, const Rational& b) {return static_cast<Rational>(a) + static_cast<Rational>(b);}
Rational operator-(int a, const Rational& b) {return static_cast<Rational>(a) - static_cast<Rational>(b);}
Rational operator*(int a, const Rational& b) {return static_cast<Rational>(a) * static_cast<Rational>(b);}
Rational operator/(int a, const Rational& b) {return static_cast<Rational>(a) / static_cast<Rational>(b);}

Rational operator+(const Rational& a, int b) {return static_cast<Rational>(a) + static_cast<Rational>(b);}
Rational operator-(const Rational& a, int b) {return static_cast<Rational>(a) - static_cast<Rational>(b);}
Rational operator*(const Rational& a, int b) {return static_cast<Rational>(a) * static_cast<Rational>(b);}
Rational operator/(const Rational& a, int b) {return static_cast<Rational>(a) / static_cast<Rational>(b);}

Rational operator+(const BigInteger& a, const Rational& b) {return static_cast<Rational>(a) + static_cast<Rational>(b);}
Rational operator-(const BigInteger& a, const Rational& b) {return static_cast<Rational>(a) - static_cast<Rational>(b);}
Rational operator*(const BigInteger& a, const Rational& b) {return static_cast<Rational>(a) * static_cast<Rational>(b);}
Rational operator/(const BigInteger& a, const Rational& b) {return static_cast<Rational>(a) / static_cast<Rational>(b);}

Rational operator+(const Rational& a, const BigInteger& b) {return static_cast<Rational>(a) + static_cast<Rational>(b);}
Rational operator-(const Rational& a, const BigInteger& b) {return static_cast<Rational>(a) - static_cast<Rational>(b);}
Rational operator*(const Rational& a, const BigInteger& b) {return static_cast<Rational>(a) * static_cast<Rational>(b);}
Rational operator/(const Rational& a, const BigInteger& b) {return static_cast<Rational>(a) / static_cast<Rational>(b);}

std::string Rational::toString() const
{
    if (denominator_ == BigInteger(1))
        return numerator_.toString();

    return (numerator_.toString() + '/' + denominator_.toString());
}

std::string Rational::asDecimal(size_t precision) const {
    std::string answer;

    BigInteger Int = numerator_ / denominator_;
    if (((denominator_ < 0)||(numerator_ < 0)) && Int == 0) {
        answer += '-';
    }

    Int = Int.abs();
    answer += Int.toString();

    BigInteger Degree_of_ten = 1;
    for (size_t i = 0; i < precision + 1; ++i) {
        Degree_of_ten *= 10;
    }

    if (precision > 0) {
        BigInteger Float = ((numerator_ * Degree_of_ten) / denominator_).abs();
        Float -= Int * Degree_of_ten;

        if (Float % 10 >= 5) {
            Float += 10;
        }
        Float /= 10;

        answer.push_back('.');
        answer.insert(answer.end(), precision - Float.size(),'0');

        answer += Float.toString();
    }

    return answer;
}

Rational::operator double() const {
    std::string strRat = asDecimal(308);

    return stod(strRat);
}

Rational Rational::abs() const {
    return Rational(numerator_.abs(), denominator_);
}

double CharToDigit(char l) {
    return static_cast<double> (l - '0');
}

std::ostream& operator<<(std::ostream& output, const Rational& rational) {
    output << rational.toString();

    return output;
}

std::istream& operator>>(std::istream& input, Rational& rational) {
    int x = 0;
    input >> x;

    rational = Rational(x);

    return input;
}