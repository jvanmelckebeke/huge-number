//
// Created by Jari on 14/01/2022.
//

#include <iostream>
#include "testhelper.h"
#include "bigassnumber.h"

using namespace std;

void showTest(const string &operation, sll num1, sll num2, const BigAssNumber &a, const BigAssNumber &b, sll expected,
         const BigAssNumber &actual) {

    cout << "[ testing " << operation << " ]" << endl;

    cout << "[EXPECT] " << num1 << " " << operation << " " << num2 << " = " << expected << endl;
    cout << "[ACTUAL] (" << a << " " << operation << " " << b << ") == " << actual << endl;
    cout << "[ACTUAL] " << a.numValue() << " " << operation << " " << b.numValue() << " = " << actual.numValue()
         << endl;
    cout << "[RESULT] " << ((actual.numValue() == expected) ? "PASS" : "FAIL OR OVERFLOW") << endl;
    cout << endl;
}

void doTest(sll num1, sll num2) {
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
    showTest("/", num1, num2, a, b, num1 / num2, a / b);
    cout << "=== END TEST ===" << endl;
}