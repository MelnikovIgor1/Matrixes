//
// Created by Игорь Мельников on 03.04.2020.
//

#include "BigIneger.h"


BigInteger::BigInteger() :
        array_ (),
        sign (true) {

}

BigInteger::BigInteger(long long int n) :
        array_(),
        sign (true) {
    if (n == 0)
        return;

    sign = (n >= 0);

    n = ::abs(n);

    while (n > 0) {
        array_.push_back(static_cast<long int>(n % Base));

        n /= Base;
    }


}

BigInteger &BigInteger::operator +=(const BigInteger& other){
    if (sign == other.sign) {
        if (array_.size() < other.array_.size()) {
            array_.resize(other.array_.size());
        }

        for (size_t i = 0; i < other.array_.size(); ++i) {
            array_[i] += other.array_[i];
        }

        move_normal_digits();
    } else {
        sign = !sign;
        *this -= other;
        sign = !sign;
    }

    if (array_.empty()) {
        sign = true;
    }

    return *this;
}

void BigInteger::move_normal_digits() {
    for (size_t i = 0; i < array_.size(); ++i) {
        if (array_[i] >= Base) {
            if (i == array_.size() - 1) {
                array_.push_back(array_[i]/Base);
            } else {
                array_[i+1] += array_[i]/Base;
            }

            array_[i] %= Base;
        }
    }
}

bool BigInteger::operator >(const BigInteger& other) const {
    if (sign && !other.sign)
        return true;
    if (!sign && other.sign)
        return false;
    if (sign)
        return abs_more(other);

    return other.abs_more(*this)||other == *this;
}

bool BigInteger::operator ==(const BigInteger& other) const {
    if (sign != other.sign)
        return false;

    if (array_.size() > other.array_.size()) {
        return false;
    } else if (array_.size() < other.array_.size()) {
        return false;
    } else {
        for (int i = static_cast<int>(array_.size()) - 1; i >= 0; --i) {
            if (array_[i] != other.array_[i]) {
                return false;
            }
        }
    }

    return true;
}

bool BigInteger::operator >=(const BigInteger& other) const {
    return (*this == other)||(*this > other);
}

bool BigInteger::abs_more(const BigInteger &other) const {
    if (array_.size() > other.array_.size()) {
        return true;
    } else if (array_.size() < other.array_.size()) {
        return false;
    } else {
        for (int i = static_cast<int>(array_.size())-1; i >= 0; --i) {
            if (array_[i] > other.array_[i]) {
                return true;
            } else if (array_[i] < other.array_[i]) {
                return false;
            }
        }
    }

    return false;
}

BigInteger &BigInteger::operator -=(const BigInteger& other) {
    if (sign == other.sign) {
        if (abs_more(other)) {
            for (size_t i = 0; i < other.array_.size(); ++i) {
                array_[i] -= other.array_[i];
            }

            make_array_positive();
        } else {
            array_.resize(other.array_.size());
            for (size_t i = 0; i < other.array_.size(); ++i) {
                array_[i] = other.array_[i] - array_[i];
            }

            sign = !sign;
            make_array_positive();
        }

        for (int i = static_cast<int>(array_.size()) - 1; i >= 0; --i) {
            if (array_[i] != 0)
                break;

            array_.pop_back();
        }

        if (array_.empty()) {
            sign = true;
        }
    } else {
        sign = !sign;
        *this += other;
        sign = !sign;

        if (array_.empty()) {
            sign = true;
        }
    }

    if (array_.empty()) {
        sign = true;
    }

    return *this;
}

void BigInteger::make_array_positive() {
    for (size_t i = 0; i < array_.size(); ++i) {
        if (array_[i] < 0) {
            --array_[i + 1];
            array_[i] += Base;
        }
    }
}

void BigInteger::Dump() const {
    if (!sign) {
        std::cout << "-";
    }

    if (array_.empty()) {
        std::cout << 0;
    } else {
        for (int i = static_cast<int>(array_.size()) - 1; i >= 0; --i) {
            std::cout << array_[i] << ",";
        }
    }

    std::cout << "\n";
}

BigInteger BigInteger::operator +(const BigInteger& other) const {
    BigInteger x (0);
    x += *this;
    x += other;

    return x;
}

BigInteger BigInteger::operator -(const BigInteger& other) const {
    BigInteger x (0);
    x += *this;
    x -= other;

    return x;
}

bool BigInteger::operator !=(const BigInteger& other) const {
    return !(*this == other);
}

bool BigInteger::operator <(const BigInteger& other) const {
    return other > *this;
}

bool BigInteger::operator <=(const BigInteger& other) const {
    return other >= *this;
}

BigInteger &BigInteger::operator *=(const BigInteger & b) {
    *this = *this * b;

    return *this;
}

BigInteger BigInteger::operator *(const BigInteger& b) const {
    BigInteger answer;
    answer.sign = !(sign ^ b.sign);
    answer.array_.resize (array_.size() + b.array_.size() + 3);

    for (size_t i = 0; i < array_.size(); ++i) {
        for (size_t j = 0; j < b.array_.size(); ++j) {
            answer.array_[i + j] += array_[i] * b.array_[j];
        }
    }

    answer.move_normal_digits();

    for (int i = static_cast<int>(answer.array_.size()) - 1; i >= 0; --i) {
        if (answer.array_[i] != 0)
            break;

        answer.array_.pop_back();
    }

    if (answer.array_.empty()) {
        answer.sign = true;
    }

    return answer;
}

BigInteger BigInteger::operator /(const BigInteger& b) const {
    auto a = *this; a.sign = true;
    BigInteger B  = b; B.sign = true;
    int x (0);
    BigInteger y (0);
    BigInteger t (0);

    while (!b.abs_more(a)) {
        B = b; B.sign = true;
        size_t r = 0;

        B.array_.insert(B.array_.begin(), a.array_.size() - b.array_.size(), 0);

        r = a.array_.size() - b.array_.size();

        if (B > a) {
            --r;
            B.array_.erase(B.array_.begin());
        }

        x = find(a, B);

        y += BigInteger(x).pow(r);

        a -= B * x;
    }

    y.sign = (sign == b.sign);

    if (y.array_.empty()) {
        y.sign = true;
    }

    return y;
}

BigInteger& BigInteger::operator *=(const int& n) {
    if (n < 0)
        sign = !sign;

    for (long & i : array_) {
        i *= n;
    }

    move_normal_digits();

    return *this;
}

BigInteger BigInteger::operator *(const int& n) const {
    BigInteger answ = *this;
    answ *= n;
    return answ;
}

BigInteger BigInteger::operator %(const BigInteger& b) const {
    return *this - (*this / b)*b;
}

BigInteger &BigInteger::operator /=(const BigInteger& b) {
    *this = *this / b;
    return *this;
}

bool BigInteger::operator ==(int  n) const {
    return *this == BigInteger(n);
}

BigInteger BigInteger::abs() const {
    BigInteger a = *this;
    a.sign = true;

    return a;
}


BigInteger NOD (BigInteger a, BigInteger b) {
    return a.QuickNOD(b);
}

BigInteger BigInteger::operator -() const {
    BigInteger answer = *this;
    answer.sign = !answer.sign;

    if (answer.array_.empty()) {
        answer.sign = true;
    }

    return answer;
}

void BigInteger::fromString(std::string str) {
    int sz = str.length();
    int szWithoutSign = sz;
    array_.clear();
    sign = true;

    int min = 0;
    if (str[0] == '-') {
        sign = false;
        --szWithoutSign;
        min = 1;
    }

    for (int i = 0; i < szWithoutSign; i += Deg) {
        array_.push_back(stoi(str.substr(std::max(sz - i - Deg, min), Deg)));
    }

    for (int i = static_cast<int>(array_.size()) - 1; i >= 0; --i) {
        if (array_[i] != 0)
            break;

        array_.pop_back();
    }
}

std::string BigInteger::toString() const {
    std::string BigStr;

    if (!sign) {
        BigStr.push_back('-');
    }

    if (array_.empty()) {
        BigStr = '0';
    } else {
        size_t sz = array_.size();
        std::string add;

        for (size_t i = 0; i < sz; ++i) {
            add = std::to_string(array_[sz - i - 1]);
            if (i > 0) {
                add.insert(add.begin(), Deg - add.size(), '0');
            }

            BigStr.append(add);
        }
    }

    return BigStr;
}

bool BigInteger::operator >(int n) const {
    return *this>BigInteger(n);
}

bool BigInteger::operator <(int n) const {
    return *this<BigInteger(n);
}

bool BigInteger::operator >=(int n) const
{
    return *this>=BigInteger(n);
}

BigInteger BigInteger::pow(size_t n) {
    BigInteger answer = *this;
    answer.array_.insert(answer.array_.begin(), n, 0);
    return answer;
}

size_t BigInteger::size() {
    if (*this == 0) {
        return 0;
    }

    size_t answer = array_.size() * Deg;

    for (int i = 1000; i > 1; i /= 10)
    {
        if (array_.back() < i) {
            --answer;
        }

    }

    return answer;
}

int find(const BigInteger& a, const BigInteger& b) {
    int step = 131072/8;

    int d = 0;

    while (step > 0) {
        if (b * (d + step) <= a) {
            d += step;
        }

        step /= 2;
    }

    return d;
}


BigInteger BigInteger::QuickNOD(const BigInteger& other) const {
    if (*this == 0) {
        return other;
    }

    if (other == 0) {
        return *this;
    }

    BigInteger my_copy = this->abs();

    BigInteger a = other;
    BigInteger answer = 1;

    a.sign = true;
    while (my_copy != a) {
        if (my_copy.array_[0] % 2) {
            if (a.array_[0] % 2) {
                if (a > my_copy) {
                    a -= my_copy;
                } else {
                    my_copy -= a;
                }
            } else {
                a.Quick_divide_by_2();
            }
        } else {
            if (a.array_[0] % 2) {
                my_copy.Quick_divide_by_2();
            } else {
                answer *= 2;
                my_copy.Quick_divide_by_2();
                a.Quick_divide_by_2();
            }
        }
    }

    answer *= a;
    return answer;
}

BigInteger& BigInteger::Quick_divide_by_2() {
    size_t sz = array_.size();

    bool from_upper = false;
    for (size_t i = 0; i < sz; ++i) {
        if (from_upper) {
            array_[sz - i - 1] += Base;
        }

        from_upper = (bool)(array_[sz - i - 1]%2);
        array_[sz - i - 1] /= 2;
    }

    for (int i = static_cast<int>(array_.size()) - 1; i >= 0; --i) {
        if (array_[i] != 0)
            break;

        array_.pop_back();
    }

    return *this;
}
