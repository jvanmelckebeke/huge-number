//
// Created by Jari on 14/01/2022.
//

#include "bignumber.h"

int BigNumber::getUnits(int current) const {
    if (sign) {
        return current;
    }
    return next->getUnits(current + 1);
}

BigNumber &BigNumber::addRang(unit amount) {
    if (next) {
        *next += amount;
    } else {
        next = new BigNumber(amount );
        sign = none;
    }

    return *this;
}

BigNumber &BigNumber::addToRang(int rang, sll amount) {
    if (rang == 0) {
        *this += amount;
        return *this;
    }

    if (sign) {
        next = new BigNumber();
        next->sign = sign;
        sign = none;
    }

    next->addToRang(rang - 1, amount);
    return *this;

}

BigNumber &BigNumber::removeRang(unit amount) {
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
        next = new BigNumber(amount);
        next->sign = sign;
        *next = next->negate();
    }


    return *this;
}