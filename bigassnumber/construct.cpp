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

BigAssNumber::BigAssNumber(const string &numberString) {
    if (numberString.empty()) {
        value = 0;
        sign = positive;
        next = nullptr;
        return;
    }

    int lastIdx = numberString.length() - 1;
    char lastChar = numberString[lastIdx];

    value = lastChar - '0';

    if (lastIdx) {

        char before = numberString[lastIdx - 1];

        if (isdigit(before)) {
            sign = none;
            next = new BigAssNumber(numberString.substr(0, lastIdx));
        } else if (before == '-') {
            sign = negative;
        }
    } else {
        sign = positive;
    }
    next = nullptr;

}

// copy constructor
BigAssNumber::BigAssNumber(const BigAssNumber &copy) : value(copy.value), sign(copy.sign) {
    if (copy.next)
        next = new BigAssNumber(*copy.next);
    else
        next = nullptr;
}


// destructor
BigAssNumber::~BigAssNumber() {
    value = 0;
    sign = none;
    next = nullptr;
}