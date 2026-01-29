#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QDateTime>
#include <QPushButton>
#include <QPainter>
#include <QTime>

#include "AnalogClock.h"

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

    QTimer time;

    //Button per cambiare il formato dell'ora
    QPushButton buttonAMPM("AM/PM", &window);
    buttonAMPM.setGeometry(75,250,150,50);
    bool AMPM = false;

    //Button per cambiare Analogico/Digitale
    QPushButton buttonAD("Analogico", &window);
    buttonAD.setGeometry(75,320,150,50);
    bool analogTime = false;


    //Aggiornamento tempo
    QObject::connect(&time, &QTimer::timeout, [&]() {
        QString format = AMPM? "hh:mm:ss AP":"HH:mm:ss";
        QString time = QDateTime::currentDateTime().toString(format);
        digitalTimeLabel.setText(time);

        analogClock.update();
    });

    QObject::connect(&buttonAMPM, &QPushButton::clicked, [&]() {
        AMPM = !AMPM;

        QString buttonTextAMPM = AMPM ? "24h" : "AM/PM";
        buttonAMPM.setText(buttonTextAMPM);
    });

    QObject::connect(&buttonAD, &QPushButton::clicked, [&]() {
        analogTime = !analogTime;

        digitalTimeLabel.setVisible(!analogTime);
        analogClock.setVisible(analogTime);

        QString buttonTextAD = analogTime ? "Digitale" : "Analogico";
        buttonAD.setText(buttonTextAD);
    });



    time.start(1000);

    window.show();
    return app.exec();
}