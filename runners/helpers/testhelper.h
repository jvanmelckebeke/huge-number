//
// Created by Jari on 14/01/2022.
//

#ifndef RANDOM_PRIMES_TESTHELPER_H
#define RANDOM_PRIMES_TESTHELPER_H

#include <cmath>
#include <iostream>
#include "Timer.h"
#include "bignumber.h"

#define MODULUS 1000

typedef long long int sll;

void showCompactTestHeader();

void showCompactTest(const string &operation, TimeDuration duration, bool isPass);

template<typename T>
class Test {
private:
    T bignumber1, bignumber2;

    sll number1, number2;

    Timer timer;

    void showTest(const string &operation, TimeDuration duration, sll expected, const T &actual) {
        cout << "[[ testing " << operation << " ]]" << endl;

        cout << "[EXPECT NUM] " << number1 << " " << operation << " " << number2 << " = " << expected << endl;
        cout << "[ACTUAL OBJ] " << bignumber1 << " " << operation << " " << bignumber2 << " = " << actual
             << endl;
        cout << "[ACTUAL NUM] " << bignumber1.numValue() << " " << operation << " " << bignumber2.numValue()
             << " = "
             << actual.numValue()
             << endl;
        cout << "[RESULT NUM] " << ((actual.numValue() == expected) ? "PASS" : "FAIL OR OVERFLOW") << endl;
        cout << "[DURATION  ] " << duration_cast<microseconds>(duration).count() << " us" << endl;
        cout << endl;
    }

public:
    Test(sll num1, sll num2, bool doPow, bool showExpanded) {
        timer = Timer();
        number1 = num1;
        number2 = num2;

        bignumber1 = T(num1);
        bignumber2 = T(num2);

        T modulus = T(MODULUS);


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
        T actualSum = bignumber1 + bignumber2;
        TimeDuration durationSum = timer.lapTimer();

        T actualDiff = bignumber1 - bignumber2;
        TimeDuration durationDiff = timer.lapTimer();

        T actualProduct = bignumber1 * bignumber2;
        TimeDuration durationProduct = timer.lapTimer();

        T actualDivision = bignumber1 / bignumber2;
        TimeDuration durationDivision = timer.lapTimer();

        T actualRemainder = bignumber1 % bignumber2;
        TimeDuration durationRemainder = timer.lapTimer();

        T actualPower = T(0);
        TimeDuration durationPower = timer.lapTimer();

        if (doPow) {
            actualPower = pow<T>(bignumber1, bignumber2);
            durationPower = timer.lapTimer();
        }

        T actualPowMod = powMod<T>(bignumber1, bignumber2, modulus);
        TimeDuration durationPowMod = timer.lapTimer();

        if (showExpanded) {
            showTest("+", durationSum, num1 + num2, actualSum);
            showTest("-", durationDiff, num1 - num2, actualDiff);
            showTest("*", durationProduct, num1 * num2, actualProduct);
            showTest("/", durationDivision, num1 / num2, actualDivision);
            showTest("%", durationRemainder, num1 % num2, actualRemainder);

            if (doPow) {
                showTest("^", durationPower, pow(num1, num2), actualPower);
            }
            showTest("^%", durationPowMod, ((sll) pow(num1, num2)) % MODULUS, actualPowMod);
        }
        cout << "== TIME DURATION ==" << endl;

        showCompactTestHeader();
        showCompactTest("+", durationSum, num1 + num2 == actualSum.numValue());
        showCompactTest("-", durationDiff, num1 - num2 == actualDiff.numValue());
        showCompactTest("*", durationProduct, num1 * num2 == actualProduct.numValue());
        showCompactTest("/", durationDivision, num1 / num2 == actualDivision.numValue());
        showCompactTest("%", durationRemainder, num1 % num2 == actualRemainder.numValue());

        if (doPow) { showCompactTest("^", durationPower, pow(num1, num2) == actualPower.numValue()); }
        showCompactTest("^%", durationPowMod, ((sll) pow(num1, num2)) == actualPowMod.numValue());

        cout << "=== END TEST ===" << endl << endl;
    }
};

#endif //RANDOM_PRIMES_TESTHELPER_H
