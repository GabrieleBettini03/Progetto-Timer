//
// Created by Gabriele Bettini on 30/01/2026.
//

#include <filesystem>
#include "Timer.h"
#include <string>

Timer::Timer() {
    seconds = 0;
    status = "timerStop";
}

void Timer::startTimer() {
    status = "timerStart";
}

void Timer::stopTimer() {
    status = "timerStop";
}

void Timer::resetTimer() {
   status = "timerStop";
}

void Timer::decreaseTimer() {
    if (status == "timerStart") {
        if (seconds >= 0) seconds--;
        else stopTimer();
    }
}