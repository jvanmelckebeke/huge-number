//
// Created by Jari on 14/01/2022.
//

#include "bigassnumber.h"

BigAssNumber::BigAssNumber() {
    value = 0;
    sign = positive;
    next = nullptr;
}

BigAssNumber::BigAssNumber(sll number) {
    if (number >= MAX_UNIT) {
        sign = none;
        value = number % MAX_UNIT;
        next = new BigAssNumber(number / MAX_UNIT);
    } else {
        sign = GETSIGN(number);
        value = ABS(number);
        next = nullptr;
    }
}


// destructor
BigAssNumber::~BigAssNumber() {
    value = 0;
    sign = none;
    next = nullptr;
}