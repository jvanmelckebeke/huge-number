//
// Created by Jari on 14/01/2022.
//

#include "linkedbignumber.h"

constexpr Sign negateSign(Sign sign) {
    switch (sign) {
        case positive:
            return negative;
        case negative:
            return positive;
        case none:
            return none;
        default:
            return none;
    }
}

void LinkedBigNumber::setFrom(const LinkedBigNumber &other) {
    value = other.value;
    sign = other.sign;

    if (other.next) {
        next = new LinkedBigNumber(other.next->copy());
    } else { next = nullptr; }
}

void LinkedBigNumber::setSign(Sign nSign) {
    if (next) {
        next->setSign(nSign);
    } else {
        sign = nSign;
    }
}

Sign LinkedBigNumber::getSign() const {
    if (sign) { // none is defined as 0 in enum Sign
        return sign;
    }
    return next->getSign();
}

LinkedBigNumber LinkedBigNumber::negate() const {
    LinkedBigNumber c = copy();

    if (sign) {
        c.sign = negateSign(c.sign);
    } else {
        c.next = new LinkedBigNumber(c.next->negate());
    }

    return c;
}

LinkedBigNumber LinkedBigNumber::abs() const {
    LinkedBigNumber cpy = copy();
    cpy.setSign(positive);
    return cpy;
}

LinkedBigNumber LinkedBigNumber::copy() const {
    LinkedBigNumber cpy = LinkedBigNumber(*this);
    return cpy;
}

sll LinkedBigNumber::numValue() const {
    sll result = value;

    sll rang = MAX_UNIT;

    LinkedBigNumber c = copy();

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

