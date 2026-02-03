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


    //getters & setters
    std::string getStatus() {
        return status;
    };

    int getSeconds() {
        return seconds;
    };

    void setSeconds(int s) {
        seconds = s;
    }

    bool getTimerFinished() {
        return timerFinished;
    }

    void setTimerFinished(bool tf) {
        timerFinished = tf;
    }

private:
    int seconds;
    std::string status;
    bool timerFinished;
};


#endif //PROGETTO_TIMER_TIMER_H