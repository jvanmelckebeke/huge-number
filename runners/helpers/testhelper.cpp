//
// Created by Jari on 14/01/2022.
//

#include <iostream>
#include <iomanip>
#include <chrono>

#include "Timer.h"
#include "testhelper.h"

using namespace std;
using namespace std::chrono;


void showCompactTestHeader() {
    cout << "operation | result | time taken" << endl;
    cout << "========= | ====== | ==========" << endl;
}

void showCompactTest(const string &operation, TimeDuration duration, bool isPass) {
    cout << setw(5) << right << operation << "    " << " |  " << (isPass ? "PASS" : "FAIL") << "  | "
         << duration_cast<microseconds>(duration).count() << " us" << endl;
}

