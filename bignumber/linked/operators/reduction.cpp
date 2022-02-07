//
// Created by Jari on 17/01/2022.
//

#include "../linkedbignumber.h"

LinkedBigNumber LinkedBigNumber::operator-(const LinkedBigNumber &b) const {
    LinkedBigNumber cpy = copy();
    cpy -= b;
    return cpy;
}

LinkedBigNumber &LinkedBigNumber::operator-=(const LinkedBigNumber &b) {
    if (getSign() != b.getSign()) {
        *this += b.negate();
        return *this;
    }

    if (*this < b) {
        LinkedBigNumber result = b - *this;
        LinkedBigNumber negated = result.negate();
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
