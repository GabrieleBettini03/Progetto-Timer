//
// Created by Gabriele Bettini on 30/01/2026.
//

#include <filesystem>
#include "Timer.h"
#include <string>
#include <iostream>

Timer::Timer() {
    seconds = 0;
    status = "idle";
}

void Timer::startTimer() {
    status = "counting";
}

void Timer::stopTimer() {
    status = "paused";
}

void Timer::resetTimer() {
   status = "idle";
}

void Timer::decreaseTimer() {
    if (status == "counting") {
        if (seconds > 0) {
            seconds--;
            std::cout << seconds << std::endl;
        }
        else stopTimer();
    }
}