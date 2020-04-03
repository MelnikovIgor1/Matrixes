//
// Created by Игорь Мельников on 03.04.2020.
//

#include "BaseMatrix.h"

template<typename Field>
BaseMatrix<Field>::BaseMatrix(unsigned N, unsigned M, bool rand_) :
        array_(),
        N_(N),
        M_(M) {
    array_.resize(N_);

    for (auto& i : array_) {
        i.resize(M_);
    }

    for (auto& i : array_) {
        for (auto& j : i) {
            j = Field(0);
        }
    }

    if (rand_ && N_ == M_) {
        for (unsigned i = 0; i < N_; ++i) {
            array_[i][i] = Field(1);
        }
    }
}


template<typename Field>
BaseMatrix<Field>& BaseMatrix<Field>::operator+=(const BaseMatrix<Field>& x) {
    for (unsigned i = 0; i < N_; ++i) {
        for (unsigned j = 0; j < M_; ++j) {
            array_[i][j] += x.array_[i][j];
        }
    }

    return (*this);
}

template<typename Field>
void BaseMatrix<Field>::Dump() const {
    for (auto& i : array_) {
        for (auto& j : i) {
            j.Dump();
        }

        std::cout << "\n";
    }

    std::cout << "\n";
}

template<typename Field>
BaseMatrix<Field> &BaseMatrix<Field>::operator -=(const BaseMatrix<Field>& x) {
    for (unsigned i = 0; i < N_; ++i) {
        for (unsigned j = 0; j < M_; ++j) {
            array_[i][j] -= x.array_[i][j];
        }
    }

    return (*this);
}

template<typename Field>
BaseMatrix<Field> BaseMatrix<Field>::operator *(const Field& f) const {
    BaseMatrix<Field> answer = *this;

    for (unsigned i = 0; i < N_; ++i) {
        for (unsigned j = 0; j < M_; ++j) {
            answer.array_[i][j] *= f;
        }
    }

    return answer;
}

template <typename Field>
BaseMatrix<Field> operator *(const Field& k, const BaseMatrix<Field>& m) {
    BaseMatrix<Field> answer (m.N, m.M);
    for (unsigned i = 0; i < answer.N(); ++i) {
        for (unsigned j = 0; j < answer.M(); ++j) {
            answer.array_[i][j] = m.array_[i][j] * k;
        }
    }

    return answer;
}

template<typename Field>
BaseMatrix<Field> BaseMatrix<Field>::operator*(const BaseMatrix & x) const {
    unsigned length = lower_2_degree(std::max(std::max(N(), M()), std::max(x.N(), x.M())));
    BaseMatrix<Field> A(length, length, true);
    BaseMatrix<Field> B(length, length, true);

    A.copy_in(std::make_pair(unsigned(0), unsigned(0)), *this);
    B.copy_in(std::make_pair(unsigned(0), unsigned(0)), x);

    return (A.multiply_if_degree_of_2(B)).SubMatrix(0, 0, N(), x.M());
}

template<typename Field>
std::vector<BaseMatrix<Field>> BaseMatrix<Field>::Split() const {
    std::vector<BaseMatrix<Field>> answer;

    answer.push_back(SubMatrix(0, 0, N_/2, M_/2));
    answer.push_back(SubMatrix(N_/2, 0, N_/2, M_/2));
    answer.push_back(SubMatrix(0, M_/2, N_/2, M_/2));
    answer.push_back(SubMatrix(N_/2, M_/2, N_/2, M_/2));

    return answer;
}

template<typename Field>
BaseMatrix<Field> BaseMatrix<Field>::SubMatrix(unsigned x, unsigned y, unsigned n, unsigned m) const {
    BaseMatrix<Field> answer(n, m);

    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < m; ++j) {
            answer.array_[i][j] = array_[i + x][j + y];
        }
    }

    return answer;
}

template<typename Field>
void BaseMatrix<Field>::copy_in(std::pair<unsigned, unsigned> coordinates, const BaseMatrix& matrix_) {
    for (unsigned i = 0; i < matrix_.N(); ++i) {
        for (unsigned j = 0; j < matrix_.M(); ++j) {
            array_[i + coordinates.first][j + coordinates.second] = matrix_.array_[i][j];
        }
    }
}

template<typename Field>
BaseMatrix<Field> BaseMatrix<Field>::Expanded_matrix(std::pair<unsigned, unsigned> lenth) const {
    BaseMatrix<Field> answer(lenth.first, lenth.second);

    answer.copy_in(std::make_pair(unsigned(0), unsigned(0)), *this);

    return answer;
}

template<typename Field>
BaseMatrix<Field> BaseMatrix<Field>::multiply_if_degree_of_2(const BaseMatrix& matrix_) const {
    if (N() <= 16) {
        auto answer = QuickMultiply(matrix_);
        return answer;
    }

    auto A = Split();
    auto B = matrix_.Split();

    auto P1 = (A[0] + A[3]).multiply_if_degree_of_2(B[0] + B[3]);
    auto P2 = (A[1] + A[3]).multiply_if_degree_of_2(B[0]);
    auto P3 = (A[0]).multiply_if_degree_of_2(B[2] - B[3]);
    auto P4 = (A[3]).multiply_if_degree_of_2(B[1] - B[0]);
    auto P5 = (A[0] + A[2]).multiply_if_degree_of_2(B[3]);
    auto P6 = (A[1] - A[0]).multiply_if_degree_of_2(B[0] + B[2]);
    auto P7 = (A[2] - A[3]).multiply_if_degree_of_2(B[1] + B[3]);

    std::vector<BaseMatrix<Field>> C_parts;

    C_parts.push_back(P1 + P4 - P5 + P7);
    C_parts.push_back(P2 + P4);
    C_parts.push_back(P3 + P5);
    C_parts.push_back(P1 - P2 + P3 + P6);

    return Combine(C_parts);
}

template<typename Field>
BaseMatrix<Field> BaseMatrix<Field>::QuickMultiply(const BaseMatrix<Field>& matrix) const {
    BaseMatrix<Field> Result(N_, matrix.M_);
    Field null = Field(0);

    for (unsigned i = 0; i < N_; ++i) {
        for (unsigned j = 0; j < matrix.M_; ++j) {
            Result.array_[i][j] = null;
            for (unsigned k = 0; k < M_; ++k) {
                Result.array_[i][j] += array_[i][k] * matrix.array_[k][j];
            }
        }
    }

    return Result;
}

template<typename Field>
BaseMatrix<Field> BaseMatrix<Field>::operator +(const BaseMatrix<Field>& x) const {
    BaseMatrix<Field> answer(N(), M());

    answer += x;
    answer += *this;

    return answer;
}

template<typename Field>
BaseMatrix<Field> BaseMatrix<Field>::operator -(const BaseMatrix<Field>& x) const {
    BaseMatrix<Field> answer(N(), M());

    answer -= x;
    answer += *this;

    return answer;
}

template<typename Field>
Field BaseMatrix<Field>::trace() const {
    Field answer(0);

    for (unsigned i = 0; i < N(); ++i) {
        answer += array_[i][i];
    }

    return answer;
}

template<typename Field>
unsigned BaseMatrix<Field>::Diagonalise() {
    std::pair<unsigned, unsigned> position(0, 0);

    while (position.first < N() && position.second < M()) {
        for (unsigned i = position.first; i < N(); ++i) {
            if (array_[i][position.second] != Field(0)) {
                SwapLines_(i, position.first);

                break;
            }

            if (i == N() - 1) {
                position.second += 1;
                i = 0;

                if (position.second >= M())
                    break;
            }
        }

        if (position.second >= M())
            break;

        for (unsigned i = 0; i < position.first; ++i) {
            SubtractLines_(i, position.first, array_[i][position.second]/array_[position.first][position.second]);
        }

        for (unsigned i = position.first + 1; i < N(); ++i) {
            SubtractLines_(i, position.first, array_[i][position.second]/array_[position.first][position.second]);
        }

        position.first += 1;
        position.second += 1;
    }

    return position.first;
}

template<typename Field>
void BaseMatrix<Field>::SwapLines_(unsigned l1, unsigned l2) {
    if (l1 != l2) {
        std::swap(array_[l1], array_[l2]);
    }
}

template<typename Field>
void BaseMatrix<Field>::SubtractLines_(unsigned l1, unsigned l2, Field k) {
    for (unsigned i = 0; i < M(); ++i) {
        array_[l1][i] -= array_[l2][i]*k;
    }
}

template<typename Field>
Field BaseMatrix<Field>::det() const {
    auto x = *this;

    x.Diagonalise();
    Field answer = Field(1);

    for (unsigned i = 0; i < x.N(); ++i)
    {
        answer *= x.array_[i][i];
    }

    return answer;
}

template<typename Field>
BaseMatrix<Field> BaseMatrix<Field>::transposed() const {
    BaseMatrix<Field> matrix_(M(), N());

    for (unsigned i = 0; i < M(); ++i) {
        for (unsigned j = 0; j < N(); ++j) {
            matrix_.array_[i][j] = array_[j][i];
        }
    }

    return matrix_;
}

template<typename Field>
unsigned BaseMatrix<Field>::rank() const {
    BaseMatrix<Field> m = *this;

    unsigned answer = m.Diagonalise();

    return answer;
}

template<typename Field>
BaseMatrix<Field>::BaseMatrix(std::initializer_list<std::initializer_list<Field>> list) :
        array_(),
        N_(),
        M_() {
    for (auto x : list) {
        array_.emplace_back(x);
    }

    N_ = array_.size();
    M_ = (array_.size() == 0)? 0 : array_[0].size();
}

template<typename Field>
std::vector<Field> &BaseMatrix<Field>::operator[](unsigned index_) {
    return array_[index_];
}

template<typename Field>
BaseMatrix<Field> BaseMatrix<Field>::inverted() const {
    if (N() != M()) {
        std::cout << "Mistake 777\n";
    }

    BaseMatrix<Field> matrix_(N(), N() * 2);

    matrix_.copy_in(std::make_pair(0u, 0u), *this);
    matrix_.copy_in(std::make_pair(0u, N()), BaseMatrix<Field>::One(N()));

    matrix_.Diagonalise();

    for (unsigned i = 0; i < N(); ++i) {
        for (unsigned j = N(); j < N() * 2; ++j) {
            matrix_[i][j] /= matrix_[i][i];
        }
    }

    return matrix_.SubMatrix(0u, N(), N(), N());
}

template<typename Field>
BaseMatrix<Field> BaseMatrix<Field>::One(unsigned Sz) {
    BaseMatrix<Field> answer(Sz, Sz);

    for (unsigned i = 0; i < Sz; ++i) {
        answer.array_[i][i] = Field(1);
    }

    return answer;
}

template<typename Field>
void BaseMatrix<Field>::invert() {
    *this = inverted();
}

template<typename Field>
const std::vector<Field> &BaseMatrix<Field>::operator[](unsigned index_) const {
    return array_[index_];
}

template<typename Field>
std::vector<Field> BaseMatrix<Field>::getRow(unsigned index_) const {
    return array_[index_];
}

template<typename Field>
std::vector<Field> BaseMatrix<Field>::getColumn(unsigned index_) const {
    std::vector<Field> answer;

    for (unsigned i = 0; i < N(); ++i) {
        answer.push_back(array_[i][index_]);
    }

    return answer;
}

template<typename Field>
bool BaseMatrix<Field>::operator!=(const BaseMatrix <Field>& other) const {
    return array_ != other.array_;
}

template<typename Field>
BaseMatrix<Field> &BaseMatrix<Field>::operator*=(const BaseMatrix<Field>& other) {
    *this = *this * other;
    return *this;
}

template<typename Field>
BaseMatrix<Field> &BaseMatrix<Field>::operator *=(const Field& f) {
    *this = *this * f;
    return *this;
}

template<typename Field>
std::vector<BaseMatrix<Field>> BaseMatrix<Field>::otherSplit() const {
    std::vector<BaseMatrix<Field>> answer;

    if (N_ % 2 == 0) {
        answer.push_back(SubMatrix(0, 0, N_ / 2, M_ / 2));
        answer.push_back(SubMatrix(N_ / 2, 0, N_ / 2, M_ / 2));
        answer.push_back(SubMatrix(0, M_ / 2, N_ / 2, M_ / 2));
        answer.push_back(SubMatrix(N_ / 2, M_ / 2, N_ / 2, M_ / 2));
    } else {
        answer.push_back(SubMatrix(0, 0, (N_+1) / 2, (M_+1) / 2));
        answer.push_back(SubMatrix((N_+1) / 2, 0, N_ / 2, (M_+1) / 2));
        answer.push_back(SubMatrix(0, (M_+1) / 2, (N_+1) / 2, M_ / 2));
        answer.push_back(SubMatrix((N_+1) / 2, (M_+1) / 2, N_ / 2, M_ / 2));

        answer[1].array_.push_back(std::vector<Field>(answer[1].array_.size(), Field(0)));
        answer[3].array_.push_back(std::vector<Field>(answer[3].array_.size(), Field(0)));

        for (auto i : answer[2].array_) {
            i.push_back(Field(0));
        }

        for (auto i : answer[3].array_) {
            i.push_back(Field(0));
        }
    }

    return answer;
}

unsigned lower_2_degree(unsigned n) {
    unsigned value = 1;

    while (true) {
        if (value >= n) {
            return value;
        }

        value *= 2;
    }
}

template <typename Field>
BaseMatrix<Field> Combine(const std::vector<BaseMatrix<Field>>& vector_) {
    BaseMatrix<Field> answer(vector_[0].N() + vector_[1].N(), vector_[0].M() + vector_[2].M());

    answer.copy_in(std::make_pair(unsigned(0), unsigned(0)), vector_[0]);
    answer.copy_in(std::make_pair(unsigned(vector_[0].N()), unsigned(0)), vector_[1]);
    answer.copy_in(std::make_pair(unsigned(0), unsigned(vector_[0].M())), vector_[2]);
    answer.copy_in(std::make_pair(unsigned(vector_[0].N()), unsigned(vector_[0].M())), vector_[3]);

    return answer;
}

