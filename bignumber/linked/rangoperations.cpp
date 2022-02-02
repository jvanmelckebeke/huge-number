//
// Created by Jari on 14/01/2022.
//

#include "linkedbignumber.h"

int LinkedBigNumber::getUnits(int current) const {
    if (!next) {
        return current;
    }
    return next->getUnits(current + 1);
}

LinkedBigNumber &LinkedBigNumber::addRang(unit amount) {
    if (next) {
        *next += amount;
    } else {
        next = new LinkedBigNumber(amount);
        sign = none;
    }

    return *this;
}

LinkedBigNumber &LinkedBigNumber::addToRang(int rang, sll amount) {
    if (rang == 0) {
        *this += amount;
        return *this;
    }

    if (sign) {
        next = new LinkedBigNumber();
        next->sign = sign;
        sign = none;
    }

    next->addToRang(rang - 1, amount);
    return *this;

}

LinkedBigNumber &LinkedBigNumber::removeRang(unit amount) {
    if (next) {
        if (next->value >= amount) {
            next->value -= amount;
        } else {
            next->removeRang(1);
            next->value = MAX_UNIT - amount;
        }

        if (next->value == 0 && next->sign) {
            sign = next->sign;
            next = nullptr;
        }
    } else {
        next = new LinkedBigNumber(amount);
        next->sign = sign;
        *next = next->negate();
    }


    return *this;
}