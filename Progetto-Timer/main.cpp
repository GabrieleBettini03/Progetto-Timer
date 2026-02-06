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
#include <QDate>
#include <QCalendarWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedLayout>
#include "AnalogClock.h"
#include "Timer.h"

int fxd_Btn_Wdt = 100;
int fxd_Btn_Hgt = 50;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;

    //Finestra
    window.resize(300, 600);
    window.setWindowTitle("Timer");

    //----------------------------------------------------------------------------------------------------------------//
    //--------------------------------------------------- WIDGETS ----------------------------------------------------//
    //----------------------------------------------------------------------------------------------------------------//

    QTimer timeTicker; //"Ticker" per scandire i secondi

    Timer timer; //Timer

    //===================//
    //===== DISPLAY =====//
    //===================//

    //Label per Orologio Digitale
    QLabel digitalTimeLabel(&window);
    digitalTimeLabel.setAlignment(Qt::AlignCenter);
    digitalTimeLabel.setStyleSheet("font-size: 24px;");

    //Widget e Layout per Orologio Analogico
    AnalogClock analogClock(&window);
    analogClock.setFixedSize(200,200);
                                                                                        //Creo un altro layout e widget per centrare analogClock (a dimensione fissata), perchè non centrabile in QStackedLayout
    QWidget *analogClockWidget = new QWidget;                                           //  QStackedLayout:
    QHBoxLayout *analogClockLayout = new QHBoxLayout(analogClockWidget);                //   - Widget -> digitalTimeLabel
                                                                                        //   - Widget -> QHBoxLayout:
    analogClockLayout->addStretch();                                                    //                - analogClock
    analogClockLayout->addWidget(&analogClock,0,Qt::AlignCenter);      //   - Widget -> ...
    analogClockLayout->addStretch();

    //Label per il Timer
    QLabel timerLabel ("00 : 00 : 00",&window);
    timerLabel.setAlignment(Qt::AlignCenter);
    timerLabel.setStyleSheet("font-size: 24px;");

    //Label per la Data e Widget per il Calendario
    QDate date = QDate::currentDate();
    QString dateString = date.toString("dd/MM/yyyy");

    QLabel dateLabel(&window);
    dateLabel.setAlignment(Qt::AlignCenter);
    dateLabel.setStyleSheet("font-size: 24px;");

    QCalendarWidget calendar(&window);
    calendar.setMinimumSize(400,300);
    calendar.setMaximumSize(1000,700);

    QWidget *dateDisplayWidget = new QWidget;
    QVBoxLayout *dateDisplayLayout = new QVBoxLayout(dateDisplayWidget);

    dateDisplayLayout->addStretch();
    dateDisplayLayout->addWidget(&dateLabel);
    dateDisplayLayout->addSpacing(50);
    dateDisplayLayout->addWidget(&calendar,0,Qt::AlignCenter);
    dateDisplayLayout->addStretch();

    QStackedLayout *displayLayout = new QStackedLayout;

    displayLayout->addWidget(&digitalTimeLabel);
    displayLayout->addWidget(analogClockWidget);
    displayLayout->addWidget(&timerLabel);
    displayLayout->addWidget(dateDisplayWidget);

    //=============================================================//


    //===================//
    //=== TIMER INPUT ===//
    //===================//

    QSpinBox spinHours(&window);
    QSpinBox spinMinutes(&window);
    QSpinBox spinSeconds(&window);

    spinHours.setRange(0, 24);
    spinHours.setValue(0);
    spinHours.setSuffix(" H");

    spinMinutes.setRange(0, 59);
    spinMinutes.setValue(0);
    spinMinutes.setSuffix(" m");

    spinSeconds.setRange(0, 59);
    spinSeconds.setValue(0);
    spinSeconds.setSuffix(" s");

    QLabel sep1(" :", &window);
    QLabel sep2(" :", &window);

    QHBoxLayout *timeInputLayout = new QHBoxLayout;

    timeInputLayout->addStretch();
    timeInputLayout->addWidget(&spinHours);
    timeInputLayout->addWidget(&sep1);
    timeInputLayout->addWidget(&spinMinutes);
    timeInputLayout->addWidget(&sep2);
    timeInputLayout->addWidget(&spinSeconds);
    timeInputLayout->addStretch();

    QWidget timeInputWidget(&window);
    timeInputWidget.setLayout(timeInputLayout);
    timeInputWidget.setVisible(false);

    //=============================================================//


    //===================//
    //== TIMER BUTTONS ==//
    //===================//

    QPushButton timerStart("Start", &window);
    timerStart.setFixedSize(fxd_Btn_Wdt,fxd_Btn_Hgt);
    QPushButton timerPauseResume("Pause", &window);
    timerPauseResume.setFixedSize(fxd_Btn_Wdt,fxd_Btn_Hgt);
    QPushButton timerReset("Reset", &window);
    timerReset.setFixedSize(fxd_Btn_Wdt,fxd_Btn_Hgt);

    QHBoxLayout *timerButtonsLayout = new QHBoxLayout;

    timerButtonsLayout->addStretch();

    timerButtonsLayout->addWidget(&timerStart);
    timerButtonsLayout->addWidget(&timerPauseResume);
    timerButtonsLayout->addWidget(&timerReset);

    timerButtonsLayout->addStretch();

    QWidget timerButtonsWidget(&window);
    timerButtonsWidget.setLayout(timerButtonsLayout);
    timerButtonsWidget.setVisible(false);

    //=============================================================//

    //==================//
    //== MODE BUTTONS ==//
    //==================//

    QPushButton digitalTimeFormatButton("AM/PM", &window);
    digitalTimeFormatButton.setFixedSize(fxd_Btn_Wdt,fxd_Btn_Hgt);
    bool AMPM = false;
    QPushButton digitalAnalogButton("Analogico", &window);
    digitalAnalogButton.setFixedSize(fxd_Btn_Wdt,fxd_Btn_Hgt);
    bool analogTime = false;
    QPushButton timerScreenButton("Timer", &window);
    timerScreenButton.setFixedSize(fxd_Btn_Wdt,fxd_Btn_Hgt);
    bool timerScreen = false;
    QPushButton dateButton("Date", &window);
    dateButton.setFixedSize(fxd_Btn_Wdt,fxd_Btn_Hgt);
    bool dateScreen = false;

    QHBoxLayout *modeButtonsLayout = new QHBoxLayout;

    modeButtonsLayout->addStretch();

    modeButtonsLayout->addWidget(&digitalTimeFormatButton);
    modeButtonsLayout->addWidget(&digitalAnalogButton);
    modeButtonsLayout->addWidget(&timerScreenButton);
    modeButtonsLayout->addWidget(&dateButton);

    modeButtonsLayout->addStretch();

    //=============================================================//

    //===================//
    //=== MAIN LAYOUT ===//
    //===================//

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->addLayout(displayLayout);
    mainLayout->addWidget(&timeInputWidget);
    mainLayout->addWidget(&timerButtonsWidget);
    mainLayout->addLayout(modeButtonsLayout);
    mainLayout->addStretch();

    window.setLayout(mainLayout);

    //=============================================================//



    //----------------------------------------------------------------------------------------------------------------//
    //------------------------------------------------- CONNESSIONI --------------------------------------------------//
    //----------------------------------------------------------------------------------------------------------------//

    //Aggiornamento tempo
    QObject::connect(&timeTicker, &QTimer::timeout, [&]() {
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
    QObject::connect(&digitalTimeFormatButton, &QPushButton::clicked, [&]() {
        AMPM = !AMPM;

        QString buttonTextAMPM = AMPM ? "24h" : "AM/PM";
        digitalTimeFormatButton.setText(buttonTextAMPM);
    });

    //Segnale button Digitale/Analogico
    QObject::connect(&digitalAnalogButton, &QPushButton::clicked, [&]() {
        analogTime = !analogTime;

        if (!timerScreen && !dateScreen) {
            if (analogTime) displayLayout->setCurrentIndex(1);
            else  displayLayout->setCurrentIndex(0);
        }

        QString buttonTextAD = analogTime ? "Digitale" : "Analogico";
        digitalAnalogButton.setText(buttonTextAD);
    });

    //Segnale button Timer
    QObject::connect(&timerScreenButton, &QPushButton::clicked, [&]() {
        timerScreen = !timerScreen;
        if (dateScreen) {
            dateScreen = false;
            dateButton.setText("Data");
        }

        if (timerScreen) displayLayout->setCurrentIndex(2);
        else {
            if (analogTime) displayLayout->setCurrentIndex(1);
            else  displayLayout->setCurrentIndex(0);
        }

        timeInputWidget.setVisible(timerScreen);
        timerButtonsWidget.setVisible(timerScreen);

        QString buttonTextTimer = timerScreen ? "Orologio" : "Timer";
        timerScreenButton.setText(buttonTextTimer);
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

    //Segnale Button Date
    QObject::connect(&dateButton, &QPushButton::clicked, [&]() {
        dateScreen = !dateScreen;
        if (timerScreen) {
            timerScreen = false;
            timeInputWidget.setVisible(false);
            timerButtonsWidget.setVisible(false);
            timerScreenButton.setText("Timer");
        }

        if (dateScreen) displayLayout->setCurrentIndex(3);
        else {
            if (analogTime) displayLayout->setCurrentIndex(1);
            else  displayLayout->setCurrentIndex(0);
        }

        QString buttonTextDate = dateScreen ? "Orario" : "Data";
        dateButton.setText(buttonTextDate);

        dateLabel.setText(dateString);
    });

    timeTicker.start(1000);

    window.show();
    return app.exec();
}