//
// Created by Jari on 17/01/2022.
//


#include "../linkedbignumber.h"

LinkedBigNumber LinkedBigNumber::operator*(sll number) const {
    return *this *LinkedBigNumber(number);
}

LinkedBigNumber LinkedBigNumber::operator*(const LinkedBigNumber &other) const {
    Sign resultSign = (getSign() == other.getSign()) ? positive : negative;


    LinkedBigNumber result = LinkedBigNumber();

    int ranga = 0;

    LinkedBigNumber a = copy();

    while (true) {


        LinkedBigNumber b = other.copy();
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


LinkedBigNumber &LinkedBigNumber::operator*=(sll number) {
    *this *= LinkedBigNumber(number);

    return *this;
}

LinkedBigNumber &LinkedBigNumber::operator*=(const LinkedBigNumber &b) {
    *this = *this * b;
    return *this;
}