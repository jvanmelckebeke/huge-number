//
// Created by Jari on 17/01/2022.
//

#include "bignumber.h"

BigNumber BigNumber::operator-(sll num) const {
    BigNumber cpy = copy();
    cpy -= BigNumber(num);
    return cpy;
}

BigNumber BigNumber::operator-(const BigNumber &b) const {
    BigNumber cpy = copy();
    cpy -= b;
    return cpy;
}

BigNumber &BigNumber::operator-=(sll number) {
    *this -= BigNumber(number);
    return *this;
}

BigNumber &BigNumber::operator-=(const BigNumber &b) {
    if (getSign() != b.getSign()) {
        *this += b.negate();
        return *this;
    }

    if (*this < b) {
        BigNumber result = b - *this;
        BigNumber negated = result.negate();
        setFrom(negated);
        return *this;
    }

    if (value < b.value) {
        removeRang(1);
        value += MAX_UNIT - b.value;
    } else {
        value -= b.value;
    }

    if (b.next && next) {
        *next -= *b.next;

        if (next->value == 0 && next->sign) {
            sign = next->sign;
            next = nullptr;
        }

    }

    return *this;
}
