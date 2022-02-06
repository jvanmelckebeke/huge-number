//
// Created by jarivm on 1/02/22.
//

#ifndef RANDOM_PRIMES_BIGNUMBER_H
#define RANDOM_PRIMES_BIGNUMBER_H

#include <ostream>

using namespace std;


typedef long long int sll;


template<typename T>
class BigNumber;

template<typename T>
class DivisionResult {
public:
    T result;
    T remainder;
};

enum Sign {
    none = 0, positive = 1, negative = -1
};

constexpr Sign invertSign(Sign sign) {
    switch (sign) {
        case positive:
            return negative;
        case negative:
            return positive;
        case none:
            return none;
    }
}

template<class T>
class BigNumber {
public:

    friend T powMod(const T &base, const T &exponent, const T &modulo);

    friend T pow(const T &base, const T &exponent);

    friend ostream &operator<<(ostream &os, const BigNumber &number) {
        os << number.to_string();
        return os;
    }

    explicit operator std::string() {
        return to_string();
    }

    virtual void setSign(Sign nSign) = 0;

    [[nodiscard]] virtual Sign getSign() const = 0;

    virtual T operator+(const T &b) const = 0;


    virtual T &operator+=(const T &b) = 0;


    virtual T operator-(const T &b) const = 0;


    virtual T &operator-=(const T &b) = 0;


    virtual T operator*(const T &b) const = 0;


    virtual T &operator*=(const T &b) = 0;


    virtual T operator/(const T &b) const = 0;


    virtual T &operator/=(const T &b) = 0;


    virtual T operator%(const T &b) const = 0;


    virtual T &operator%=(const T &b) = 0;


    //equality
    virtual bool operator==(const T &rhs) const = 0;

    virtual bool operator!=(const T &rhs) const = 0;


    //compare
    virtual bool operator<(const T &rhs) const = 0;

    virtual bool operator>(const T &rhs) const {
        const T a = *this;
        return rhs < a;
    }

    virtual bool operator<=(const T &rhs) const {
        return !(*this > rhs);
    };

    virtual bool operator>=(const T &rhs) const {
        return !(*this < rhs);
    };


    //misc
    virtual T copy() const = 0;

    [[nodiscard]] virtual T negate() const {
        T cpy = copy();
        cpy.setSign(invertSign(getSign()));

        return cpy;
    };

    virtual T abs() const {
        T cpy = copy();
        cpy.setSign(positive);
        return cpy;
    };

    virtual void setFrom(const T &other) = 0;

    [[nodiscard]] virtual sll numValue() const = 0;

    [[nodiscard]] virtual string to_string() const = 0;


};


template<typename T>
typename std::enable_if<is_base_of<BigNumber<T>, T>::value, T>::type
powMod(const T &base, const T &exponent, const T &modulo) {
    T result = T(1);

    T b = base.abs() % modulo;
    T exp = exponent.copy();

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * b) % modulo;
        }

        b = (b * b) % modulo;
        exp /= 2;
    }

    return result;
}

template<typename T>
typename std::enable_if<is_base_of<BigNumber<T>, T>::value, T>::type
pow(const T &base, const T &exponent) {
    T result = 1; // fixme: this is dirty, but works beautifully


    T b = base.copy().abs();
    T exp = exponent.copy();

    while (exp > 0) {
        if (exp % 2 == 1) {
            result *= b;
        }

        b *= b;

        exp /= 2;
    }

    if (exponent % 2 != 0) {
        result.setSign(base.getSign());
    }

    return result;
}

#endif //RANDOM_PRIMES_BIGNUMBER_H
