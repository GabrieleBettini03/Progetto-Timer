//
// Created by Gabriele Bettini on 10/02/2026.
//


#include <QtTest/QTest>
#include "Timer.h"
#include "TestTimer.h"

void TestTimer::initialState() {
    Timer t;
    QCOMPARE(t.getStatus(), std::string("idle"));
    QCOMPARE(t.getSeconds(), 0);
    QCOMPARE(t.getTimerFinished(), false);
}

void TestTimer::startTimer() {
    Timer t;
    t.startTimer();
    QCOMPARE(t.getStatus(), std::string("counting"));
}

void TestTimer::stopTimer() {
    Timer t;
    t.startTimer();
    t.stopTimer();
    QCOMPARE(t.getStatus(), std::string("paused"));
}

void TestTimer::decreaseTimer() {
    Timer t;
    t.setSeconds(5);
    t.startTimer();
    t.decreaseTimer();
    QCOMPARE(t.getSeconds(), 4);
}

void TestTimer::finishTimer() {
    Timer t;
    t.setSeconds(1);
    t.startTimer();
    t.decreaseTimer();
    t.decreaseTimer();
    QCOMPARE(t.getStatus(), std::string("idle"));
    QCOMPARE(t.getTimerFinished(), true);
}

QTEST_MAIN(TestTimer)