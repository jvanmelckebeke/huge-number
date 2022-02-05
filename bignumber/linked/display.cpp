//
// Created by Jari on 14/01/2022.
//

#include "linkedbignumber.h"

string LinkedBigNumber::to_string() const {
    string out;
    switch (sign) {
        case positive:
            out = std::to_string(value);
            break;
        case negative:
            out = "-" + std::to_string(value);
            break;
        case none:
            out = next->to_string() + std::to_string(value);
            break;
        default:
            out = "";
    }
    return out;
}