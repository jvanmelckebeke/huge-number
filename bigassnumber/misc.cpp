//
// Created by Jari on 14/01/2022.
//


#include "bigassnumber.h"


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

void BigAssNumber::setFrom(const BigAssNumber &other) {
    value = other.value;
    sign = other.sign;

    if (other.next) {
        next = new BigAssNumber(other.next->copy());
    } else { next = nullptr; }
}

void BigAssNumber::setSign(Sign nSign) {
    if (next) {
        next->setSign(nSign);
    } else {
        sign = nSign;
    }
}

Sign BigAssNumber::getSign() const {
    if (sign) { // none is defined as 0 in enum Sign
        return sign;
    }
    return next->getSign();
}

BigAssNumber BigAssNumber::negate() const {
    BigAssNumber c = copy();

    c.setSign(negateSign(c.getSign()));

    return c;
}

BigAssNumber BigAssNumber::abs() const {
    BigAssNumber cpy = copy();
    cpy.setSign(positive);
    return cpy;
}

BigAssNumber BigAssNumber::copy() const {
    BigAssNumber cpy = BigAssNumber();

    cpy.sign = sign;
    cpy.value = value;
    if (next) {
        cpy.next = new BigAssNumber(next->copy());
    } else {
        cpy.next = nullptr;
    }

    return cpy;

}

sll BigAssNumber::numValue() const {
    sll result = value;

    sll rang = MAX_UNIT;

    BigAssNumber c = copy();

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