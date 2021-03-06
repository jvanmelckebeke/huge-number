//
// Created by Jari on 14/01/2022.
//


#include <iostream>
#include "helpers/testhelper.h"
#include "linked/linkedbignumber.h"


typedef LinkedBigNumber BigNumberImpl;

int main() {
    // AUTO TEST
    sll ns[] = {16, 10001, 64, 999, 12345678987654321,
                255511525,
                123456789987654321,
                73086254633065,
                7200417529881855,
                8526951391258878282,
                8569513912588782822};
    cout << "=== VARS ===" << endl;
    for (auto num: ns) {
        cout << num << " = " << BigNumberImpl(num) << endl;
    }

    cout << "=== END VARS ===" << endl;

    for (auto num1: ns) {

        for (auto num2: ns) {
            Test<BigNumberImpl>(num1, num2, false, false);
        }
    }
}