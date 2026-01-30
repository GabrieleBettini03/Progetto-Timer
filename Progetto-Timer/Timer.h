//
// Created by Gabriele Bettini on 30/01/2026.
//

#ifndef PROGETTO_TIMER_TIMER_H
#define PROGETTO_TIMER_TIMER_H

#include <string>

class Timer {
public:
    Timer();

    void startTimer();
    void stopTimer();
    void resetTimer();
    void decreaseTimer();

    std::string getStatus() {
        return status;
    };

    int getSeconds() {
        return seconds;
    };

    void setSeconds(int s) {
        seconds = s;
    }

private:
    int seconds;
    std::string status;
};


#endif //PROGETTO_TIMER_TIMER_H