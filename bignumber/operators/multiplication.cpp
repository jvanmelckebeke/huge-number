//
// Created by Jari on 17/01/2022.
//


#include "bignumber.h"

BigNumber BigNumber::operator*(sll number) const {
    return *this * BigNumber(number);
}

BigNumber BigNumber::operator*(const BigNumber &other) const {
    Sign resultSign = (getSign() == other.getSign()) ? positive : negative;


    BigNumber result = BigNumber();

    int ranga = 0;

    BigNumber a = copy();

    while (true) {


        BigNumber b = other.copy();
        int rangb = 0;

        result.addToRang(ranga + rangb, a.value * b.value);

        while (b.next) {

            b = *b.next;

            rangb++;
            result.addToRang(ranga + rangb, a.value * b.value);
        }


        if (a.next) {
            a = *a.next;
            ranga++;
        } else {
            result.setSign(resultSign);
            return result;
        }
    }
}


BigNumber &BigNumber::operator*=(sll number) {
    *this *= BigNumber(number);

    return *this;
}

BigNumber &BigNumber::operator*=(const BigNumber &b) {
    *this = *this * b;
    return *this;
}