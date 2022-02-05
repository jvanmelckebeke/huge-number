//
// Created by Jari on 14/01/2022.
//
#include "linkedbignumber.h"

#pragma region equality

bool LinkedBigNumber::operator==(sll number) const {
    return *this == LinkedBigNumber(number);
}

bool LinkedBigNumber::operator==(const LinkedBigNumber &rhs) const {

    if (sign && rhs.sign) {
        return sign == rhs.sign && value == rhs.value;
    }

    if (sign != rhs.sign) {
        return false;
    }

    if (value == rhs.value) {
        return *next == *rhs.next;
    }

    return false;
}

bool LinkedBigNumber::operator!=(sll number) const {
    return *this != LinkedBigNumber(number);
}

bool LinkedBigNumber::operator!=(const LinkedBigNumber &rhs) const {
    return sign != rhs.sign || value != rhs.value || !(*this == rhs);
}

#pragma endregion

#pragma region compare numbers

bool LinkedBigNumber::operator<(sll number) const {
    if (sign) {
        return value * sign < number;
    }

    Sign fullSign = getSign();

    if (fullSign != GETSIGN(number)) {
        return fullSign < GETSIGN(number);
    }

    if (number == 0) {
        return fullSign == negative;
    }

    return *this < LinkedBigNumber(number);
}

bool LinkedBigNumber::operator<=(sll number) const {
    return *this <= LinkedBigNumber(number);
}

bool LinkedBigNumber::operator>=(sll number) const {
    return LinkedBigNumber(number) <= *this;
}

#pragma endregion


#pragma region compare BigNumbers

bool LinkedBigNumber::operator<(const LinkedBigNumber &rhs) const {
    // recursively compare signs
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
        default:
            return true;
    }
}

bool LinkedBigNumber::operator<=(const LinkedBigNumber &rhs) const {
    return !(rhs < *this);
}

bool LinkedBigNumber::operator>=(const LinkedBigNumber &rhs) const {
    return !(*this < rhs);
}



#pragma endregion