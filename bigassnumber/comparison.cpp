//
// Created by Jari on 14/01/2022.
//
#include "bigassnumber.h"

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
    return sign != rhs.sign || value != rhs.value || !(*this == rhs);
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