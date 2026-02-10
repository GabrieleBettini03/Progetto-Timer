//
// Created by Gabriele Bettini on 10/02/2026.
//

#ifndef PROGETTO_TIMER_TESTTIMER_H
#define PROGETTO_TIMER_TESTTIMER_H

#include <QObject>

class TestTimer : public QObject {
    Q_OBJECT

    private slots:
    void initialState();
    void startTimer();
    void stopTimer();
    void decreaseTimer();
    void finishTimer();
};

#endif //PROGETTO_TIMER_TESTTIMER_H