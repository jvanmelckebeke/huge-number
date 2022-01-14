//
// Created by Jari on 07/01/2022.
//
#include <limits>
#include <iostream>
#include "hugenumber.h"

#define MAX_UNIT 10

using namespace std;

constexpr Sign negateSign(Sign sign) {
    switch (sign) {
        case positive:
            return negative;
        case negative:
            return positive;
        case none:
            return none;
    }
}

#pragma region constructors + destructor

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
    delete next;
}

#pragma endregion


#pragma region operators

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
#pragma endregion

#pragma region rang operations

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

#pragma endregion

#pragma region misc

void BigAssNumber::setFrom(BigAssNumber &other) {
    value = other.value;
    sign = other.sign;

    if (other.next) {
        next = new BigAssNumber(other.next->copy());
    } else { next = nullptr; }
}

void BigAssNumber::setSign(Sign nSign) {
    if (next) {
        next->setSign(nSign);
    } else {
        sign = nSign;
    }
}

Sign BigAssNumber::getSign() const {
    if (sign) { // none is defined as 0 in enum Sign
        return sign;
    }
    return next->getSign();
}

BigAssNumber BigAssNumber::negate() const {
    BigAssNumber c = copy();

    c.setSign(negateSign(c.getSign()));

    return c;
}

BigAssNumber BigAssNumber::abs() const {
    BigAssNumber cpy = *this;

    if (cpy < 0) {
        return cpy.negate();
    }
    return cpy;
}

BigAssNumber BigAssNumber::copy() const {
    BigAssNumber cpy = BigAssNumber();

    cpy.sign = sign;
    cpy.value = value;
    if (next) {
        cpy.next = new BigAssNumber(next->copy());
    } else {
        cpy.next = nullptr;
    }

    return cpy;

}

sll BigAssNumber::numValue() const {
    sll result = value;

    sll rang = MAX_UNIT;

    BigAssNumber c = copy();

    while (c.next) {
        c = *c.next;
        result += c.value * rang;
        rang *= MAX_UNIT;
    }

    if (getSign() == negative) {
        result *= -1;
    }

    return result;
}

#pragma endregion

#pragma region equality

bool BigAssNumber::operator==(sll number) const {
    return *this == BigAssNumber(number);
}

bool BigAssNumber::operator==(const BigAssNumber &rhs) const {
    if (sign && rhs.sign) {
        return sign == rhs.sign && value == rhs.value;
    }

    if (!sign != !rhs.sign) {
        return false;
    }

    if (value == rhs.value) {
        return *next == *rhs.next;
    }

    return false;
}

bool BigAssNumber::operator!=(const BigAssNumber &rhs) const {
    return !(rhs == *this);
}

#pragma endregion

#pragma region display

ostream &operator<<(ostream &os, const BigAssNumber &number) {

    switch (number.sign) {
        case positive:
            os << to_string(number.value);
            break;
        case negative:
            os << "-" << to_string(number.value);
            break;
        case none:
            os << string(*number.next) << to_string(number.value);
            break;
    }

    return os;
}

BigAssNumber::operator std::string() const {
    switch (sign) {
        case positive:
            return to_string(value);
        case negative:
            return "-" + to_string(value);
        case none:
            return string(*next) + to_string(value);
    }
}

#pragma endregion

#pragma region compare

bool BigAssNumber::operator<(sll number) const {
    if (getSign() != GETSIGN(number)) {
        return getSign() < GETSIGN(number);
    }

    if (number == 0) {
        return getSign() == negative;
    }

    return *this < BigAssNumber(number);
}

bool BigAssNumber::operator<(const BigAssNumber &rhs) const {
    // start with fast comparisons of the signs
    switch (sign) {
        case positive:
            switch (rhs.sign) {
                case positive:
                    return value < rhs.value;
                case negative:
                    return false;
                case none:
                    return rhs.getSign() == positive;
            }
        case negative:
            switch (rhs.sign) {
                case positive:
                    return true;
                case negative:
                    return value > rhs.value;
                case none:
                    return rhs.getSign() == positive;
            }
        case none:
            switch (rhs.sign) {
                case positive:
                case negative:
                    return getSign() == negative;
                case none:
                    if (*next == *rhs.next) {
                        return value < rhs.value;
                    }
                    return *next < *rhs.next;
            }
    }
}

bool BigAssNumber::operator>(const BigAssNumber &rhs) const {
    return rhs < *this;
}

bool BigAssNumber::operator<=(const BigAssNumber &rhs) const {
    return !(rhs < *this);
}

bool BigAssNumber::operator>=(const BigAssNumber &rhs) const {
    return !(*this < rhs);
}

#pragma endregion