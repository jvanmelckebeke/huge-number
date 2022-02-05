//
// Created by Jari on 14/01/2022.
//

#include "linkedbignumber.h"

LinkedBigNumber::LinkedBigNumber() {
    value = 0;
    sign = positive;
    next = nullptr;
}

LinkedBigNumber::LinkedBigNumber(sll number) {
    if (number >= MAX_UNIT) {
        sign = none;
        value = number % MAX_UNIT;
        next = new LinkedBigNumber(number / MAX_UNIT);
    } else {
        sign = GETSIGN(number);
        value = ABS(number);
        next = nullptr;
    }
}

LinkedBigNumber::LinkedBigNumber(const string &numberString) {
    if (numberString.empty()) {
        value = 0;
        sign = positive;
        next = nullptr;
        return;
    }

    size_t lastIdx = numberString.length() - 1;
    char lastChar = numberString[lastIdx];

    value = lastChar - '0';

    if (lastIdx) {
        char before = numberString[lastIdx - 1];

        if (isdigit(before)) {
            sign = none;
            next = new LinkedBigNumber(numberString.substr(0, lastIdx));
        return;
        } else if (before == '-') {
            sign = negative;
        }
    } else {
        sign = positive;
    }
    next = nullptr;

}

// from constructor
LinkedBigNumber::LinkedBigNumber(const LinkedBigNumber &from) : value(from.value), sign(from.sign) {
    next = from.next ? new LinkedBigNumber(*from.next) : nullptr;
}


template<class T>
LinkedBigNumber::LinkedBigNumber(const BigNumber<T> &from) : LinkedBigNumber(from.to_string()) {
}

// destructor
LinkedBigNumber::~LinkedBigNumber() {
    value = 0;
    sign = none;
    next = nullptr;
}

