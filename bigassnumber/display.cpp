//
// Created by Jari on 14/01/2022.
//

#include "bigassnumber.h"

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
