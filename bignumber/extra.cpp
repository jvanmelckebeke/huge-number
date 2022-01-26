//
// Created by Jari on 16/01/2022.
//

#include "bignumber.h"

BigNumber pow(const BigNumber &base, const BigNumber &exponent) {
    BigNumber result = BigNumber(1);

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

BigNumber powMod(const BigNumber &base, const BigNumber &exponent, const BigNumber& modulo) {
    BigNumber result = BigNumber(1);

    BigNumber b = base % modulo;
    BigNumber exp = exponent.copy();

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result *b) % modulo;
        }

        b= (b * b) % modulo;
        exp /= 2;
    }

    return result;
}