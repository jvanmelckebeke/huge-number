//
// Created by Jari on 14/01/2022.
//


#include <iostream>
#include "hugenumber.h"
#include "helpers/testhelper.h"

int main() {
    // AUTO TEST
    sll ns[] = {16, 10001,64,999,12345678987654321,
                255511525,
                123456789987654321,
                73086254633065,
                7200417529881855,
                8526951391258878282,
                8569513912588782822};
    cout << "=== VARS ===" << endl;
    for (auto num: ns) {
        cout << num << " = " << BigAssNumber(num) << endl;
    }

    cout << "=== END VARS ===" << endl;

    for (auto num1: ns) {
        BigAssNumber a = BigAssNumber(num1);

        for (auto num2: ns) {
            BigAssNumber b = BigAssNumber(num2);

            cout << "=== BEGIN TEST ===" << endl;

            cout << "--- variables ---" << endl;
            cout << "a = " << a << " = " << a.numValue() << endl;
            cout << "b = " << b << " = " << b.numValue() << endl;
            cout << "--- variables ---" << endl;

            showTest("+", num1, num2, a, b, num1 + num2, a + b);
            showTest("-", num1, num2, a, b, num1 - num2, a - b);
            showTest("*", num1, num2, a, b, num1 * num2, a * b);

            cout << "=== END TEST ===" << endl;
        }
    }
}