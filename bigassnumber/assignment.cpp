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

BigAssNumber::BigAssNumber(const string &number) {
    if (number.empty()) {
        value = 0;
        sign = positive;
        next = nullptr;
    }

    int lastIdx = number.length() - 1;
    char lastChar = number[lastIdx];

    value = lastChar - '0';

    if (lastIdx) {
        char before = number[lastIdx-1];

        if (isdigit(before)) {
            sign = none;
            next = new BigAssNumber(number.substr(0,lastIdx));
        } else if (before == '-') {
            sign = negative;
        }
    } else {

        sign = positive;
        next = nullptr;
    }
}


// destructor
BigAssNumber::~BigAssNumber() {
    value = 0;
    sign = none;
    next = nullptr;
}