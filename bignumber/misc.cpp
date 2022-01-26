//
// Created by Jari on 14/01/2022.
//


#include "bignumber.h"


constexpr Sign negateSign(Sign sign) {
    switch (sign) {
        case positive:
            return negative;
        case negative:
            return positive;
        case none:
            return none;
    }
}

void BigNumber::setFrom(const BigNumber &other) {
    value = other.value;
    sign = other.sign;

    if (other.next) {
        next = new BigNumber(other.next->copy());
    } else { next = nullptr; }
}

void BigNumber::setSign(Sign nSign) {
    if (next) {
        next->setSign(nSign);
    } else {
        sign = nSign;
    }
}

Sign BigNumber::getSign() const {
    if (sign) { // none is defined as 0 in enum Sign
        return sign;
    }
    return next->getSign();
}

BigNumber BigNumber::negate() const {
    BigNumber c = copy();

    if (sign) {
        c.sign = negateSign(c.sign);
    } else {
        c.next = new BigNumber(c.next->negate());
    }

    return c;
}

BigNumber BigNumber::abs() const {
    BigNumber cpy = copy();
    cpy.setSign(positive);
    return cpy;
}

BigNumber BigNumber::copy() const {
    BigNumber cpy = BigNumber(*this);
    return cpy;
}

sll BigNumber::numValue() const {
    sll result = value;

    sll rang = MAX_UNIT;

    BigNumber c = copy();

    while (c.next) {
        c = *c.next;
        result += c.value * rang;
        rang *= MAX_UNIT;
    }

    if (getSign() == negative) {
        result *= -1;
    }

    return result;
}