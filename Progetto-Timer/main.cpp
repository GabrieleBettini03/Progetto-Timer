#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QDateTime>
#include <QPushButton>
#include <QPainter>
#include <QTime>
#include <QSpinBox>

#include "AnalogClock.h"
#include "Timer.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;

    //Finestra
    window.resize(300, 600);
    window.setWindowTitle("Timer");

    //Label per orologio digitale
    QLabel digitalTimeLabel(&window);
    digitalTimeLabel.setAlignment(Qt::AlignCenter);
    digitalTimeLabel.setGeometry(0, 100, 300,50);
    digitalTimeLabel.setStyleSheet("font-size: 24px;");

    //Widget per orologio analogico
    AnalogClock analogClock(&window);
    analogClock.setGeometry(50,10,200,200);
    analogClock.hide();

    QTimer time; //"Ticker" per scandire i secondi
    Timer timer; //Timer

    //Button per cambiare il formato dell'ora
    QPushButton buttonAMPM("AM/PM", &window);
    buttonAMPM.setGeometry(75,250,150,50);
    bool AMPM = false;

    //Button per cambiare Analogico/Digitale
    QPushButton buttonAD("Analogico", &window);
    buttonAD.setGeometry(75,320,150,50);
    bool analogTime = false;

    //Button per passare a modalità Timer
    QPushButton buttonT("Timer", &window);
    buttonT.setGeometry(75,390,150,50);
    bool timerScreen = false;

    //SpinBox per il Timer
    QSpinBox spinHours(&window);
    QSpinBox spinMinutes(&window);
    QSpinBox spinSeconds(&window);

    QLabel labelSeparator_one(" :", &window);
    QLabel labelSeparator_two(" :", &window);

    //Ore
    spinHours.setRange(0, 24);
    spinHours.setValue(0);
    spinHours.setSuffix(" H");
    spinHours.setGeometry(8,120,82,40);

    //Minuti
    spinMinutes.setRange(0, 59);
    spinMinutes.setValue(0);
    spinMinutes.setSuffix(" m");
    spinMinutes.setGeometry(110,120,82,40);

    //Secondi
    spinSeconds.setRange(0, 59);
    spinSeconds.setValue(0);
    spinSeconds.setSuffix(" s");
    spinSeconds.setGeometry(212,120,82,40);

    labelSeparator_one.setGeometry(95,125,10,30);
    labelSeparator_two.setGeometry(197,125,10,30);

    spinHours.hide();
    spinMinutes.hide();
    spinSeconds.hide();
    labelSeparator_one.hide();
    labelSeparator_two.hide();

    //Button per Iniziare/Stoppare, e Resettare il Timer
    QPushButton timerStartPause("Start", &window);
    QPushButton timerReset("Reset", &window);
    timerStartPause.setGeometry(75, 320, 70, 50);
    timerReset.setGeometry(155, 320, 70, 50);
    timerStartPause.hide();
    timerReset.hide();

    //Aggiornamento tempo
    QObject::connect(&time, &QTimer::timeout, [&]() {
        QString format = AMPM? "hh:mm:ss AP":"HH:mm:ss";
        QString time = QDateTime::currentDateTime().toString(format);
        digitalTimeLabel.setText(time);

        analogClock.update();
    });

    //Segnale button AM/PM
    QObject::connect(&buttonAMPM, &QPushButton::clicked, [&]() {
        AMPM = !AMPM;

        QString buttonTextAMPM = AMPM ? "24h" : "AM/PM";
        buttonAMPM.setText(buttonTextAMPM);
    });

    //Segnale button Digitale/Analogico
    QObject::connect(&buttonAD, &QPushButton::clicked, [&]() {
        analogTime = !analogTime;

        digitalTimeLabel.setVisible(!analogTime * !timerScreen);
        analogClock.setVisible(analogTime * !timerScreen);

        QString buttonTextAD = analogTime ? "Digitale" : "Analogico";
        buttonAD.setText(buttonTextAD);
    });

    //Segnale button Timer
    QObject::connect(&buttonT, &QPushButton::clicked, [&]() {
        timerScreen = !timerScreen;

        buttonAMPM.setVisible(!timerScreen);
        buttonAD.setVisible(!timerScreen);

        digitalTimeLabel.setVisible(!analogTime * !timerScreen);
        analogClock.setVisible(analogTime * !timerScreen);

        timerStartPause.setVisible(timerScreen);
        timerReset.setVisible(timerScreen);

        spinHours.setVisible(timerScreen);
        spinMinutes.setVisible(timerScreen);
        spinSeconds.setVisible(timerScreen);
        labelSeparator_one.setVisible(timerScreen);
        labelSeparator_two.setVisible(timerScreen);

        QString buttonTextTimer = timerScreen ? "Orologio" : "Timer";
        buttonT.setText(buttonTextTimer);
    });

    //Segnale button Timer Start
    /*QObject::connect(&timerStartPause, &QPushButton::clicked, [&]() {
        std::string timerStatus = timer.getStatus();
        if (timerStatus == "timerStop") {

        }
    });*/

    time.start(1000);

    window.show();
    return app.exec();
}