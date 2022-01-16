//
// Created by Jari on 16/01/2022.
//

#include "bigassnumber.h"

BigAssNumber pow(const BigAssNumber &base, const BigAssNumber &exponent) {
    BigAssNumber result = BigAssNumber(1);

    BigAssNumber b = base.copy();
    BigAssNumber exp = exponent.copy();

    while (exp > 0) {
        if (exp % 2 == 1) {
            result *= b;
        }

        b *= b;

        exp /= 2;
    }

    return result;
}