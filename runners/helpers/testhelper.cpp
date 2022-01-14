//
// Created by Jari on 14/01/2022.
//

#include <iostream>
#include "testhelper.h"
#include "hugenumber.h"

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