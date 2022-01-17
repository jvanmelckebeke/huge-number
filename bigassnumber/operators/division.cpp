//
// Created by Jari on 17/01/2022.
//


#pragma region division

#include "bigassnumber.h"

DivisionResult BigAssNumber::divide(const BigAssNumber &b) const {
    BigAssNumber result = BigAssNumber();
    BigAssNumber remainder = BigAssNumber();
    BigAssNumber babs = b.abs();

    Sign resultingSign = (getSign() == b.getSign()) ? positive : negative;

    if (getUnits() < babs.getUnits()) {
        return {
                new BigAssNumber(),
                new BigAssNumber(copy())
        };
    } else if (getUnits() == babs.getUnits() || (getUnits() - 1 == babs.getUnits() && next->abs() < babs)) {
        BigAssNumber cpy = abs();

        int i = 0;

        while (cpy >= babs) {
            cpy -= babs;
            i++;
        }

        result.value = i;

        result.setSign(resultingSign);
        cpy.setSign(resultingSign);

        return {
                new BigAssNumber(result),
                new BigAssNumber(cpy)
        };
    } else {
        // meaning: getUnits() > babs.getUnits() + 1 && abs() > babs
        DivisionResult higherRangResult = next->divide(b);

        result.next = higherRangResult.result;
        result.sign = none;

        if (*higherRangResult.remainder == 0) {
            if (babs <= value) {
                // guaranties that babs only has one unit
                result.value = value / babs.value;
                remainder.value = value % babs.value;
            } else {
                result.value = 0;
                remainder.value = value;
            }
        } else {
            BigAssNumber divisionToDo = BigAssNumber(value);
            divisionToDo.sign = none;

            divisionToDo.next = new BigAssNumber(*higherRangResult.remainder);

            DivisionResult currentRangResult = divisionToDo.divide(b);

            result += *currentRangResult.result;
            remainder = *currentRangResult.remainder;
        }


        result.setSign(resultingSign);

        return {
                new BigAssNumber(result),
                new BigAssNumber(remainder)
        };
    };
}

BigAssNumber BigAssNumber::operator/(const BigAssNumber &b) const {
    return *divide(b).result;
}

BigAssNumber BigAssNumber::operator/(sll number) const {
    return *this / BigAssNumber(number);
}

BigAssNumber &BigAssNumber::operator/=(sll number) {
    *this /= BigAssNumber(number);
    return *this;
}

BigAssNumber &BigAssNumber::operator/=(const BigAssNumber &b) {
    BigAssNumber temp = *this / b;
    setFrom(temp);
    return *this;
}

#pragma endregion

#pragma region remainder

BigAssNumber BigAssNumber::operator%(const BigAssNumber &b) const {
    return *divide(b).remainder;
}

BigAssNumber BigAssNumber::operator%(sll number) const {
    return *this % BigAssNumber(number);
}

BigAssNumber &BigAssNumber::operator%=(const BigAssNumber &b) {
    BigAssNumber temp = *this % b;
    setFrom(temp);
    return *this;
}

BigAssNumber &BigAssNumber::operator%=(sll number) {
    BigAssNumber temp = *this % number;
    setFrom(temp);
    return *this;
}

#pragma endregion