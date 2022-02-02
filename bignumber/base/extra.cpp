//
// Created by Jari on 16/01/2022.
//

#include <ostream>
#include "bignumber.h"

template<typename T>
T pow(const BigNumber<T> &base, const BigNumber<T> &exponent) {
    BigNumber result = BigNumber<T>(1);

    BigNumber b = base.copy();
    BigNumber exp = exponent.copy();

    while (exp > 0) {
        if (exp % 2 == 1) {
            result *= b;
        }

        b *= b;

        exp /= 2;
    }

    return result;
}

template<typename T>
T powMod(const T &base, const T &exponent, const T &modulo) {
    BigNumber result = BigNumber<T>(1);

    BigNumber b = base % modulo;
    BigNumber exp = exponent.copy();

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * b) % modulo;
        }

        b = (b * b) % modulo;
        exp /= 2;
    }

    return result;
}