//
// Created by Jari on 14/01/2022.
//

#include <iostream>
#include <cmath>
#include <iomanip>
#include <chrono>


#include "testhelper.h"
#include "bigassnumber.h"

using namespace std;
using namespace std::chrono;

auto start = high_resolution_clock::now();
auto stop = high_resolution_clock::now();

void startTimer() {
    start = high_resolution_clock::now();
}

void stopTimer() {
    stop = high_resolution_clock::now();
}

typedef duration<long long, ratio<1, 1000000000>> TimeDuration;

TimeDuration lapTimer() {
    stopTimer();
    TimeDuration duration = (stop - start);
    startTimer();
    return duration;
}

void showTest(const string &operation, TimeDuration duration, sll number1, sll number2,
              const BigAssNumber &bignumber1, const BigAssNumber &bignumber2,
              sll expected, const BigAssNumber &actual) {

    cout << "[[ testing " << operation << " ]]" << endl;

    cout << "[EXPECT NUM] " << number1 << " " << operation << " " << number2 << " = " << expected << endl;
    cout << "[ACTUAL OBJ] " << bignumber1 << " " << operation << " " << bignumber2 << " = " << actual << endl;
    cout << "[ACTUAL NUM] " << bignumber1.numValue() << " " << operation << " " << bignumber2.numValue() << " = "
         << actual.numValue()
         << endl;
    cout << "[RESULT NUM] " << ((actual.numValue() == expected) ? "PASS" : "FAIL OR OVERFLOW") << endl;
    cout << "[DURATION  ] " << duration_cast<microseconds>(duration).count() << " us" << endl;
    cout << endl;
}

void showCompactTestHeader() {
    cout << "operation | result | time taken" << endl;
    cout << "========= | ====== | ==========" << endl;
}

void showCompactTest(const string &operation, TimeDuration duration, bool isPass) {
    cout << setw(5) << right << operation << "    " << " |  " << (isPass ? "PASS" : "FAIL") << "  | "
         << duration_cast<microseconds>(duration).count() << " us" << endl;
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

    startTimer();
    BigAssNumber actualSum = a + b;
    TimeDuration durationSum = lapTimer();

    BigAssNumber actualDiff = a - b;
    TimeDuration durationDiff = lapTimer();

    BigAssNumber actualProduct = a * b;
    TimeDuration durationProduct = lapTimer();

    BigAssNumber actualDivision = a / b;
    TimeDuration durationDivision = lapTimer();

    BigAssNumber actualRemainder = a % b;
    TimeDuration durationRemainder = lapTimer();

    BigAssNumber actualPower = pow(a, b);
    TimeDuration durationPower = lapTimer();

    showTest("+", durationSum, num1, num2, a, b, num1 + num2, actualSum);
    showTest("-", durationDiff, num1, num2, a, b, num1 - num2, actualDiff);
    showTest("*", durationProduct, num1, num2, a, b, num1 * num2, actualProduct);
    showTest("/", durationDivision, num1, num2, a, b, num1 / num2, actualDivision);
    showTest("%", durationRemainder, num1, num2, a, b, num1 % num2, actualRemainder);
    showTest("^", durationPower, num1, num2, a, b, pow(num1, num2), actualPower);

    cout << "== TIME DURATION ==" << endl;

    showCompactTestHeader();
    showCompactTest("+", durationSum, num1 + num2 == actualSum.numValue());
    showCompactTest("-", durationDiff, num1 - num2 == actualDiff.numValue());
    showCompactTest("*", durationProduct, num1 * num2 == actualProduct.numValue());
    showCompactTest("/", durationDivision, num1 / num2 == actualDivision.numValue());
    showCompactTest("%", durationRemainder, num1 % num2 == actualRemainder.numValue());
    showCompactTest("^", durationPower, pow(num1, num2) == actualPower.numValue());

    cout << "=== END TEST ===" << endl;
}