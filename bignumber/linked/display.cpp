//
// Created by Jari on 14/01/2022.
//

#include "linkedbignumber.h"

string LinkedBigNumber::to_string() const {
    switch (sign) {
        case positive:
            return std::to_string(value);
        case negative:
            return "-" + std::to_string(value);
        case none:
            return next->to_string() + std::to_string(value);
        default:
            return "";
    }
}