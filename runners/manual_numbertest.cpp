//
// Created by Jari on 30/12/2021.
//

#include "helpers/testhelper.h"
#include "linked/linkedbignumber.h"

typedef LinkedBigNumber BigNumberImpl;

int main() {
    // MANUAL TEST

    sll  num1 = -20, num2 = 30;

    Test<BigNumberImpl>(num1, num2, true, true);
}
