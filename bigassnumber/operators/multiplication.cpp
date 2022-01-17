//
// Created by Jari on 17/01/2022.
//


#include "bigassnumber.h"

BigAssNumber BigAssNumber::operator*(sll number) const {
    return *this * BigAssNumber(number);
}

BigAssNumber BigAssNumber::operator*(const BigAssNumber &other) const {
    Sign resultSign = (getSign() == other.getSign()) ? positive : negative;


    BigAssNumber result = BigAssNumber();

    int ranga = 0;

    BigAssNumber a = copy();

    while (true) {


        BigAssNumber b = other.copy();
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


BigAssNumber &BigAssNumber::operator*=(sll number) {
    *this *= BigAssNumber(number);

    return *this;
}

BigAssNumber &BigAssNumber::operator*=(const BigAssNumber &b) {
    *this = *this * b;
    return *this;
}