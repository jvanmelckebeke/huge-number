//
// Created by Jari on 30/12/2021.
//

#include <iostream>
#include "hugenumber.h"
#include "helpers/testhelper.h"

int main() {



    // MANUAL TEST

    sll num1 = 1234, num2 = 1342;
    BigAssNumber a = BigAssNumber(num1);
    BigAssNumber b = BigAssNumber(num2);

    cout << "=== BEGIN MANUAL TEST ===" << endl;

    cout << "--- variables ---" << endl;
    cout << "a = " << a << " = " << num1 << endl;
    cout << "b = " << b << " = " << num2 << endl;
    cout << "--- variables ---" << endl;

    cout << "--- basics ---" << endl;
    cout << "copy a = " << a.copy() << endl;
    cout << "copy b = " << b.copy() << endl;
    cout << "--- basics ---" << endl;

    BigAssNumber actualSum = a+b;
    BigAssNumber actualDiff = a-b;
    BigAssNumber actualProduct =a *b;

    showTest("+", num1, num2, a, b, num1 + num2, actualSum);
    showTest("-", num1, num2, a, b, num1 - num2, actualDiff);
    showTest("*", num1, num2, a, b, num1 * num2, actualProduct);

    cout << "=== END TEST ===" << endl;
}
