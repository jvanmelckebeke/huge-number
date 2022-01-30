//
// Created by Jari on 18/01/2022.
//

#ifndef RANDOM_PRIMES_TIMER_H
#define RANDOM_PRIMES_TIMER_H

#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

typedef duration<long long, ratio<1, 1000000000>> TimeDuration;
typedef time_point<system_clock, TimeDuration> TimePoint;

class Timer {


private:
    TimePoint start;
    TimePoint stop;

public:
    Timer();

    void startTimer();

    void stopTimer();

    TimeDuration lapTimer();
};


#endif //RANDOM_PRIMES_TIMER_H
