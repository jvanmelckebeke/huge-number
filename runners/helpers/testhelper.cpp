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

sll number1, number2;
BigAssNumber bignumber1, bignumber2;

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

void showTest(const string &operation, TimeDuration duration,
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
    number1 = num1;
    number2 = num2;

    bignumber1 = BigAssNumber(num1);
    bignumber2 = BigAssNumber(num2);


    cout << "=== BEGIN TEST ===" << endl;

    cout << "--- variables ---" << endl;
    cout << "a = " << bignumber1 << " = " << num1 << endl;
    cout << "b = " << bignumber2 << " = " << num2 << endl;
    cout << "--- variables ---" << endl;

    /*cout << "--- basics ---" << endl;
    cout << "copy a = " << bignumber1.copy() << endl;
    cout << "copy b = " << bignumber2.copy() << endl;
    cout << "--- basics ---" << endl;*/

    startTimer();
    BigAssNumber actualSum = bignumber1 + bignumber2;
    TimeDuration durationSum = lapTimer();

    BigAssNumber actualDiff = bignumber1 - bignumber2;
    TimeDuration durationDiff = lapTimer();

    BigAssNumber actualProduct = bignumber1 * bignumber2;
    TimeDuration durationProduct = lapTimer();

    BigAssNumber actualDivision = bignumber1 / bignumber2;
    TimeDuration durationDivision = lapTimer();

    BigAssNumber actualRemainder = bignumber1 % bignumber2;
    TimeDuration durationRemainder = lapTimer();

    BigAssNumber actualPower = powMod(bignumber1, bignumber2, bignumber2);
    TimeDuration durationPower = lapTimer();

    /*showTest("+", durationSum, num1 + num2, actualSum);
    showTest("-", durationDiff, num1 - num2, actualDiff);
    showTest("*", durationProduct, num1 * num2, actualProduct);
    showTest("/", durationDivision, num1 / num2, actualDivision);
    showTest("%", durationRemainder, num1 % num2, actualRemainder);
    showTest("^%", durationPower, pow(num1, num2), actualPower);*/

    cout << "== TIME DURATION ==" << endl;

    showCompactTestHeader();
    showCompactTest("+", durationSum, num1 + num2 == actualSum.numValue());
    showCompactTest("-", durationDiff, num1 - num2 == actualDiff.numValue());
    showCompactTest("*", durationProduct, num1 * num2 == actualProduct.numValue());
    showCompactTest("/", durationDivision, num1 / num2 == actualDivision.numValue());
    showCompactTest("%", durationRemainder, num1 % num2 == actualRemainder.numValue());
    showCompactTest("^%", durationPower, pow(num1, num2) == actualPower.numValue());

    cout << "=== END TEST ===" << endl << endl;
}