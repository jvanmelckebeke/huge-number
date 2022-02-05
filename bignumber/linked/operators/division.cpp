//
// Created by Jari on 17/01/2022.
//


#pragma region division

#include "../linkedbignumber.h"

DivisionResult<LinkedBigNumber> LinkedBigNumber::divide(const LinkedBigNumber &b) const {
    LinkedBigNumber result = LinkedBigNumber();
    LinkedBigNumber remainder = LinkedBigNumber();
    LinkedBigNumber babs = b.abs();

    Sign resultingSign = (getSign() == b.getSign()) ? positive : negative;

    if (getUnits() < babs.getUnits()) {
        return {
                LinkedBigNumber(),
                LinkedBigNumber(copy())
        };
    } else if (getUnits() == babs.getUnits() || (getUnits() - 1 == babs.getUnits() && next->abs() < babs)) {
        LinkedBigNumber cpy = abs();

        int i = 0;

        while (cpy >= babs) {
            cpy -= babs;
            i++;
        }

        result.value = i;

        result.setSign(resultingSign);
        cpy.setSign(resultingSign);

        return {
                LinkedBigNumber(result),
                LinkedBigNumber(cpy)
        };
    } else {
        // meaning: getUnits() > babs.getUnits() + 1 && abs() > babs
        DivisionResult higherRangResult = next->divide(b);

        result.next = new LinkedBigNumber(higherRangResult.result);
        result.sign = none;

        if (higherRangResult.remainder == 0) {
            if (babs <= value) {
                // guaranties that babs only has one unit
                result.value = value / babs.value;
                remainder.value = value % babs.value;
            } else {
                result.value = 0;
                remainder.value = value;
            }
        } else {
            LinkedBigNumber divisionToDo = LinkedBigNumber(value);
            divisionToDo.sign = none;

            divisionToDo.next = new LinkedBigNumber(higherRangResult.remainder);

            DivisionResult currentRangResult = divisionToDo.divide(b);

            result += currentRangResult.result;
            remainder = currentRangResult.remainder;
        }


        result.setSign(resultingSign);

        return {
                LinkedBigNumber(result),
                LinkedBigNumber(remainder)
        };
    };
}

LinkedBigNumber LinkedBigNumber::operator/(const LinkedBigNumber &b) const {
    return divide(b).result;
}


LinkedBigNumber &LinkedBigNumber::operator/=(const LinkedBigNumber &b) {
    LinkedBigNumber temp = *this / b;
    setFrom(temp);
    return *this;
}

#pragma endregion

#pragma region remainder

LinkedBigNumber LinkedBigNumber::operator%(const LinkedBigNumber &b) const {
    return divide(b).remainder;
}

LinkedBigNumber &LinkedBigNumber::operator%=(const LinkedBigNumber &b) {
    LinkedBigNumber temp = *this % b;
    setFrom(temp);
    return *this;
}


#pragma endregion