//
// Created by Jari on 14/01/2022.
//

#include <iostream>
#include <cmath>
#include <iomanip>
#include <chrono>


#include "testhelper.h"
#include "bigassnumber.h"
#include "Timer.h"

#define MODULUS 1000

using namespace std;
using namespace std::chrono;

Timer timer = Timer();

sll number1, number2;
BigAssNumber bignumber1, bignumber2;

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

void doTest(sll num1, sll num2, bool showExpanded) {
    number1 = num1;
    number2 = num2;

    bignumber1 = BigAssNumber(num1);
    bignumber2 = BigAssNumber(num2);
    BigAssNumber modulus = BigAssNumber(MODULUS);


    cout << "=== BEGIN TEST ===" << endl;

    cout << "--- variables ---" << endl;
    cout << "a = " << bignumber1 << " = " << num1 << endl;
    cout << "b = " << bignumber2 << " = " << num2 << endl;
    cout << "--- variables ---" << endl;

    /*cout << "--- basics ---" << endl;
    cout << "copy a = " << bignumber1.copy() << endl;
    cout << "copy b = " << bignumber2.copy() << endl;
    cout << "--- basics ---" << endl;*/

    timer.startTimer();
    BigAssNumber actualSum = bignumber1 + bignumber2;
    TimeDuration durationSum = timer.lapTimer();

    BigAssNumber actualDiff = bignumber1 - bignumber2;
    TimeDuration durationDiff = timer.lapTimer();

    BigAssNumber actualProduct = bignumber1 * bignumber2;
    TimeDuration durationProduct = timer.lapTimer();

    BigAssNumber actualDivision = bignumber1 / bignumber2;
    TimeDuration durationDivision = timer.lapTimer();

    BigAssNumber actualRemainder = bignumber1 % bignumber2;
    TimeDuration durationRemainder = timer.lapTimer();

/*    BigAssNumber actualPower = pow(bignumber1, bignumber2);
    TimeDuration durationPower = timer.lapTimer();*/

    BigAssNumber actualPowMod = powMod(bignumber1, bignumber2, modulus);
    TimeDuration durationPowMod = timer.lapTimer();

    if (showExpanded) {
        showTest("+", durationSum, num1 + num2, actualSum);
        showTest("-", durationDiff, num1 - num2, actualDiff);
        showTest("*", durationProduct, num1 * num2, actualProduct);
        showTest("/", durationDivision, num1 / num2, actualDivision);
        showTest("%", durationRemainder, num1 % num2, actualRemainder);
//        showTest("^", durationPower, pow(num1, num2), actualPower);
        showTest("^%", durationPowMod, ((sll) pow(num1, num2)) % MODULUS, actualPowMod);
    }
    cout << "== TIME DURATION ==" << endl;

    showCompactTestHeader();
    showCompactTest("+", durationSum, num1 + num2 == actualSum.numValue());
    showCompactTest("-", durationDiff, num1 - num2 == actualDiff.numValue());
    showCompactTest("*", durationProduct, num1 * num2 == actualProduct.numValue());
    showCompactTest("/", durationDivision, num1 / num2 == actualDivision.numValue());
    showCompactTest("%", durationRemainder, num1 % num2 == actualRemainder.numValue());
//    showCompactTest("^", durationPower, pow(num1, num2) == actualPower.numValue());
    showCompactTest("^%", durationPowMod, ((sll)pow(num1, num2)) == actualPowMod.numValue());

    cout << "=== END TEST ===" << endl << endl;
}