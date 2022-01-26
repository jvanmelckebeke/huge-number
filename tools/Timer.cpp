//
// Created by Jari on 18/01/2022.
//

#include "Timer.h"


void Timer::startTimer() {
    start = high_resolution_clock::now();
}

void Timer::stopTimer() {
    stop = high_resolution_clock::now();
}

TimeDuration Timer::lapTimer() {
    stopTimer();
    TimeDuration duration = (stop - start);
    startTimer();
    return duration;
}

Timer::Timer() {
    start = high_resolution_clock::now();
    stop = high_resolution_clock::now();
}
