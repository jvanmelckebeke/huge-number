//
// Created by Jari on 14/01/2022.
//


#include <iostream>
#include "bigassnumber.h"

#pragma region sum

BigAssNumber BigAssNumber::operator+(const BigAssNumber &b) const {
    BigAssNumber cpy = copy();
    cpy += b;
    return cpy;
}

BigAssNumber BigAssNumber::operator+(sll num) const {


    BigAssNumber cpy = copy();
    cpy += num;
    return cpy;
}

BigAssNumber &BigAssNumber::operator+=(sll number) {
    *this += BigAssNumber(number);
    return *this;
}

BigAssNumber &BigAssNumber::operator+=(const BigAssNumber &b) {
    if (getSign() != b.getSign()) {
        *this -= b.negate();
        return *this;
    }

    if (MAX_UNIT - value <= b.value) {
        value = b.value - (MAX_UNIT - value);
        addRang(1);
    } else {
        value += b.value;
    };

    if (b.next) {
        if (next) {
            *next += *b.next;
        } else {
            next = new BigAssNumber(b.next->copy());
            sign = none;
        }
    }

    return *this;
}


#pragma endregion

#pragma region minus

BigAssNumber BigAssNumber::operator-(sll num) const {
    BigAssNumber cpy = copy();
    cpy -= BigAssNumber(num);
    return cpy;
}

BigAssNumber BigAssNumber::operator-(const BigAssNumber &b) const {

    BigAssNumber cpy = copy();
    cpy -= b;

    return cpy;

}

BigAssNumber &BigAssNumber::operator-=(sll number) {
    *this -= BigAssNumber(number);
    return *this;
}

BigAssNumber &BigAssNumber::operator-=(const BigAssNumber &b) {
    if (getSign() != b.getSign()) {
        *this += b.negate();
        return *this;
    }

    if (*this < b) {
        BigAssNumber result = b.copy();
        result -= *this;
        BigAssNumber blup = result.negate();

        setFrom(blup);
        return *this;
    }

    if (b.value > value) {
        removeRang(1);
        value += MAX_UNIT - b.value;
    } else {
        value -= b.value;
    }

    if (b.next) {
        if (next) {
            *next -= *b.next;

            if (next->value == 0 && next->sign) {
                sign = next->sign;
                next = nullptr;
            }

        } else {
            cout << "something went wrong" << endl;
        }
    }

    return *this;
}


#pragma endregion

#pragma region multiplication

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

#pragma endregion

#pragma region division

BigAssNumber BigAssNumber::operator/(const BigAssNumber &b) const {
    BigAssNumber cpy = copy();
    cpy /= b;
    return cpy;
}

BigAssNumber BigAssNumber::operator/(sll number) const {
    return *this / BigAssNumber(number);
}

BigAssNumber &BigAssNumber::operator/=(sll number) {
    *this /= BigAssNumber(number);
    return *this;
}

BigAssNumber &BigAssNumber::operator/=(const BigAssNumber &b) {

}

#pragma endregion