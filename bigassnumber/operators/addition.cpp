//
// Created by Jari on 17/01/2022.
//

#include "bigassnumber.h"

BigAssNumber BigAssNumber::operator+(const BigAssNumber &b) const {
    BigAssNumber cpy = copy();
    cpy += b;
    return cpy;
}

BigAssNumber BigAssNumber::operator+(sll number) const {
    BigAssNumber cpy = copy();
    cpy += number;
    return cpy;
}

BigAssNumber &BigAssNumber::operator+=(sll number) {
    if (number >= 0) {
        if (number < MAX_UNIT - value) {
            value += number;
            return *this;
        }
    } else {
        if (ABS(number) < value) {
            value += number;
            return *this;
        }
    }

    *this += BigAssNumber(number);
    return *this;
}

BigAssNumber &BigAssNumber::operator+=(const BigAssNumber &b) {
    if (getSign() != b.getSign()) {
        *this -= b.negate();
        return *this;
    }

    if (MAX_UNIT - value <= b.value) {

        // this cannot be rewritten, because first calculating b.value - MAX_UNIT might result in a value < 0 which is problematic for an unsigned datatype
        value = b.value - (MAX_UNIT - value);

        addRang(1);
    } else {
        value += b.value;
    };

    if (b.next) {
        if (next) {
            *next += *b.next;
        } else {
            next = new BigAssNumber(*b.next);
            sign = none;
        }
    }

    return *this;
}
