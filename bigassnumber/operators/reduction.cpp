//
// Created by Jari on 17/01/2022.
//


#include <iostream>
#include "bigassnumber.h"

BigAssNumber BigAssNumber::operator-(sll num) const {
    BigAssNumber cpy = copy();
    cpy -= BigAssNumber(num);
    return cpy;
}

BigAssNumber BigAssNumber::operator-(const BigAssNumber &b) const {
    BigAssNumber cpy = copy();
    cpy -= b;
    return cpy;
}

BigAssNumber &BigAssNumber::operator-=(sll number) {
    *this -= BigAssNumber(number);
    return *this;
}

BigAssNumber &BigAssNumber::operator-=(const BigAssNumber &b) {
    if (getSign() != b.getSign()) {
        *this += b.negate();
        return *this;
    }

    if (*this < b) {
        BigAssNumber result = b.copy();
        result -= *this;
        BigAssNumber blup = result.negate();

        setFrom(blup);
        return *this;
    }

    if (b.value > value) {
        removeRang(1);
        value += MAX_UNIT - b.value;
    } else {
        value -= b.value;
    }

    if (b.next) {
        if (next) {
            *next -= *b.next;

            if (next->value == 0 && next->sign) {
                sign = next->sign;
                next = nullptr;
            }

        } else {
            cout << "something went wrong" << endl;
        }
    }

    return *this;
}
