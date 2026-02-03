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
#include <QMessageBox>

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

    //Label per il Timer
    QLabel timerLabel ("00 : 00 : 00",&window);
    timerLabel.setAlignment(Qt::AlignCenter);
    timerLabel.setStyleSheet("font-size: 24px;");
    timerLabel.setGeometry(0,50,300,50);
    timerLabel.hide();

    //Button per Iniziare, Stoppare, e Resettare il Timer
    QPushButton timerStart("Start", &window);
    QPushButton timerPauseResume("Pause", &window);
    QPushButton timerReset("Reset", &window);
    timerStart.setGeometry(75,250,150,50);
    timerPauseResume.setGeometry(75, 320, 70, 50);
    timerReset.setGeometry(155, 320, 70, 50);
    timerStart.hide();
    timerPauseResume.hide();
    timerReset.hide();

    //Aggiornamento tempo
    QObject::connect(&time, &QTimer::timeout, [&]() {
        QString format = AMPM? "hh:mm:ss AP":"HH:mm:ss";
        QString time = QDateTime::currentDateTime().toString(format);
        digitalTimeLabel.setText(time);

        analogClock.update();

        //Aggiornamento e Display del Timer
        if (timer.getStatus() == "counting") {
            int hours = timer.getSeconds() / 3600;
            int minutes = (timer.getSeconds()%3600)/60;
            int seconds = (timer.getSeconds()%3600)%60;

            std::string stringH;
            std::string stringM;
            std::string stringS;


            if (hours < 10) stringH = "0" + std::to_string(hours);
            else stringH = std::to_string(hours);

            if (minutes < 10) stringM = "0" + std::to_string(minutes);
            else stringM = std::to_string(minutes);

            if (seconds < 10) stringS = "0" + std::to_string(seconds);
            else stringS = std::to_string(seconds);

            timerLabel.setText(QString::fromStdString(stringH + " : " + stringM + " : " + stringS));
            timer.decreaseTimer();
        }
        else {
            if (timer.getStatus() == "idle" && timer.getTimerFinished()) {
                QMessageBox::warning(&window, "Timer", "Timer Over");
                timer.setTimerFinished(false);
            }
        }
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

        timerStart.setVisible(timerScreen);
        timerPauseResume.setVisible(timerScreen);
        timerReset.setVisible(timerScreen);

        spinHours.setVisible(timerScreen);
        spinMinutes.setVisible(timerScreen);
        spinSeconds.setVisible(timerScreen);
        labelSeparator_one.setVisible(timerScreen);
        labelSeparator_two.setVisible(timerScreen);

        timerLabel.setVisible(timerScreen);

        QString buttonTextTimer = timerScreen ? "Orologio" : "Timer";
        buttonT.setText(buttonTextTimer);
    });

    //Segnale Button Timer Start
    QObject::connect(&timerStart, &QPushButton::clicked, [&]() {
        std::string timerStatus = timer.getStatus();
        if (timerStatus == "idle" or timerStatus == "paused") {
            int timerTotal = spinHours.value() * 3600 + spinMinutes.value() * 60 + spinSeconds.value();
            timer.setSeconds(timerTotal);
            timer.startTimer();
            timerPauseResume.setText("Pause");
        }
    });

    //Segnale Button Timer Pause/Resume
    QObject::connect(&timerPauseResume, &QPushButton::clicked, [&]() {
        std::string timerStatus = timer.getStatus();
        if (timerStatus == "counting") {
            timerPauseResume.setText("Resume");
            timer.stopTimer();
        }
        else if (timerStatus == "paused") {
            timerPauseResume.setText("Pause");
            timer.startTimer();
        }
    });

    //Segnale Button Timer Reset
    QObject::connect(&timerReset, &QPushButton::clicked, [&]() {
        std::string timerStatus = timer.getStatus();
        if (timerStatus != "counting") {
            timerLabel.setText("00 : 00 : 00");
            timer.resetTimer();
            timerPauseResume.setText("Pause");
            spinHours.setValue(0);
            spinMinutes.setValue(0);
            spinSeconds.setValue(0);
        }
    });

    time.start(1000);

    window.show();
    return app.exec();
}