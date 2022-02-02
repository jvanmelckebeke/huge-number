//
// Created by Jari on 19/01/2022.
//

#include <iostream>
#include <fstream>
#include "LinkedBigNumber.h"
#include "Timer.h"

using namespace std;

void write_file(ofstream &outfile, const string &operation, int number1, int number2, TimeDuration duration) {
    outfile << "\"" << operation << "\"," << number1 << "," << number2 << ","
            << duration_cast<nanoseconds>(duration).count() << endl;
}

int main() {
    BigNumber modulus = BigNumber(1e6);
    Timer t = Timer();

    long long minute = time(nullptr) % 3600 / 60;
    long long hour = time(nullptr) % 86400 / 3600 + 1;

    ofstream outfile(
            R"(C:\Users\Jari\Repos\random-primes\performances\performance)" + to_string(hour) + to_string(minute) +
            ".csv");
    cout << "starting" << endl;

    outfile << R"("operation","number1","number2","duration")" << endl;

    for (int number1 = 1; number1 < 61; number1 += 1) {
        cout << number1 << endl;
        for (int number2 = 1; number2 < 61; number2 += 1) {
            BigNumber a = BigNumber(number1);
            BigNumber b = BigNumber(number2);

            t.startTimer();
            a + b;
            TimeDuration timePlus = t.lapTimer();

            write_file(outfile, "plus", number1, number2, timePlus);

            t.startTimer();
            a - b;
            TimeDuration timeMinus = t.lapTimer();

            write_file(outfile, "minus", number1, number2, timeMinus);

            t.startTimer();
            a * b;
            TimeDuration timeProduct = t.lapTimer();

            write_file(outfile, "product", number1, number2, timeProduct);

            t.startTimer();
            a / b;
            TimeDuration timeDivision = t.lapTimer();

            write_file(outfile, "division", number1, number2, timeDivision);

            t.startTimer();
            a % b;
            TimeDuration timeRemainder = t.lapTimer();

            write_file(outfile, "remainder", number1, number2, timeRemainder);

            t.startTimer();
            pow(a, b);
            TimeDuration timePower = t.lapTimer();
            write_file(outfile, "power", number1, number2, timePower);

            t.startTimer();
            powMod(a, b, modulus);
            TimeDuration timePowMod = t.lapTimer();

            write_file(outfile, "powMod", number1, number2, timePowMod);

        }
    }

    outfile.close();
    cout << "done" << endl;
}