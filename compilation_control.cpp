//
// Created by Игорь Мельников on 03.04.2020.
//
#include <cmath>

template <unsigned int P, unsigned int n>
struct prime {
    static const bool is_prime = static_cast<bool>(1 / (P % n) + 1) && prime<P, n - 2>::is_prime;
};

template <unsigned int P>
struct prime<P, 3> {
    static const bool is_prime = static_cast<bool>(1 / (P % 3) + 1) && static_cast<bool>(1 / (P % 2) + 1);
};

template <unsigned int P>
struct prime<P, 0> {
    static const bool is_prime = true;
};

template <typename Field>
class is_field
{
public:
    static void check () {
        if (Field(1)/Field(1) != Field(1)) {
            std::cerr << "Errorfield";
        }
    };
};

template <unsigned N, unsigned M>
class are_equal {
public:
    static const unsigned result = 1/ static_cast<int>(N == M);

    static void do_nothing() {}
};

template <unsigned N, unsigned M>
class are_simple {
public:
    static const unsigned result = 1/(N%M) + are_simple<N, M-1>::result;
};

template <unsigned N>
class are_simple <N, 1> {
public:
    static const unsigned result = 1;
};

template <unsigned N>
class is_prime {
public:
    static const unsigned result = are_simple<N, static_cast<int>(sqrt(static_cast<double >(N)))>::result;
};