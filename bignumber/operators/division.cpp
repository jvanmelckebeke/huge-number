//
// Created by Jari on 17/01/2022.
//


#pragma region division

#include "bignumber.h"

DivisionResult BigNumber::divide(const BigNumber &b) const {
    BigNumber result = BigNumber();
    BigNumber remainder = BigNumber();
    BigNumber babs = b.abs();

    Sign resultingSign = (getSign() == b.getSign()) ? positive : negative;

    if (getUnits() < babs.getUnits()) {
        return {
                new BigNumber(),
                new BigNumber(copy())
        };
    } else if (getUnits() == babs.getUnits() || (getUnits() - 1 == babs.getUnits() && next->abs() < babs)) {
        BigNumber cpy = abs();

        int i = 0;

        while (cpy >= babs) {
            cpy -= babs;
            i++;
        }

        result.value = i;

        result.setSign(resultingSign);
        cpy.setSign(resultingSign);

        return {
                new BigNumber(result),
                new BigNumber(cpy)
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
            BigNumber divisionToDo = BigNumber(value);
            divisionToDo.sign = none;

            divisionToDo.next = new BigNumber(*higherRangResult.remainder);

            DivisionResult currentRangResult = divisionToDo.divide(b);

            result += *currentRangResult.result;
            remainder = *currentRangResult.remainder;
        }


        result.setSign(resultingSign);

        return {
                new BigNumber(result),
                new BigNumber(remainder)
        };
    };
}

BigNumber BigNumber::operator/(const BigNumber &b) const {
    return *divide(b).result;
}

BigNumber BigNumber::operator/(sll number) const {
    return *this / BigNumber(number);
}

BigNumber &BigNumber::operator/=(sll number) {
    *this /= BigNumber(number);
    return *this;
}

BigNumber &BigNumber::operator/=(const BigNumber &b) {
    BigNumber temp = *this / b;
    setFrom(temp);
    return *this;
}

#pragma endregion

#pragma region remainder

BigNumber BigNumber::operator%(const BigNumber &b) const {
    return *divide(b).remainder;
}

BigNumber BigNumber::operator%(sll number) const {
    return *this % BigNumber(number);
}

BigNumber &BigNumber::operator%=(const BigNumber &b) {
    BigNumber temp = *this % b;
    setFrom(temp);
    return *this;
}

BigNumber &BigNumber::operator%=(sll number) {
    BigNumber temp = *this % number;
    setFrom(temp);
    return *this;
}

#pragma endregion