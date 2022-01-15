//
// Created by Jari on 14/01/2022.
//

#include "bigassnumber.h"

BigAssNumber &BigAssNumber::addRang(unit amount) {
    if (next) {
        *next += BigAssNumber(amount * getSign());
    } else {
        next = new BigAssNumber(amount * getSign());
        sign = none;
    }

    return *this;
}

BigAssNumber &BigAssNumber::addToRang(int rang, sll amount) {
    if (rang == 0) {
        *this += amount;
        return *this;
    }

    if (sign) {
        next = new BigAssNumber();
        next->sign = sign;
        sign = none;
    }

    next->addToRang(rang - 1, amount);
    return *this;

}

BigAssNumber &BigAssNumber::removeRang(unit amount) {
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
        next = new BigAssNumber(amount);
        next->sign = sign;
        *next = next->negate();
    }


    return *this;
}