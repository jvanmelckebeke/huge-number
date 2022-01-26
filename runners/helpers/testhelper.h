//
// Created by Jari on 14/01/2022.
//

#ifndef RANDOM_PRIMES_TESTHELPER_H
#define RANDOM_PRIMES_TESTHELPER_H


#include "bignumber.h"

void
showTest(const string &operation, sll number1, sll number2, const BigNumber &bignumber1, const BigNumber &bignumber2, sll expected,
         const BigNumber &actual);

void doTest(sll num1, sll num2, bool showExpanded = false);

#endif //RANDOM_PRIMES_TESTHELPER_H
