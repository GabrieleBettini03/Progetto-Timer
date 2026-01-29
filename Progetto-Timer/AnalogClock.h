//
// Created by Gabriele Bettini on 29/01/2026.
//

#ifndef PROGETTO_TIMER_ANALOGCLOCK_H
#define PROGETTO_TIMER_ANALOGCLOCK_H

#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QDateTime>
#include <QPushButton>
#include <QPainter>
#include <QTime>

class AnalogClock : public QWidget{
public:
    AnalogClock(QWidget *parent = nullptr) : QWidget(parent)
    {
        setMinimumSize(200, 200);
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QTime time = QTime::currentTime();

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        int side = qMin(width(), height());
        painter.translate(width() / 2, height() / 2);
        painter.scale(side / 200.0, side / 200.0);

        // Quadrante
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(240, 240, 240));
        painter.drawEllipse(-100, -100, 200, 200);

        painter.setPen(Qt::black);
        for (int i = 0; i < 12; ++i) {
            painter.drawLine(88, 0, 96, 0);
            painter.rotate(30.0);
        }

        // Lancetta ore
        painter.save();
        painter.setPen(QPen(Qt::black, 6));
        painter.rotate(30.0 * (time.hour() + time.minute() / 60.0));
        painter.drawLine(0, 0, 0, -50);
        painter.restore();

        // Lancetta minuti
        painter.save();
        painter.setPen(QPen(Qt::black, 4));
        painter.rotate(6.0 * time.minute());
        painter.drawLine(0, 0, 0, -70);
        painter.restore();

        // Lancetta secondi
        painter.save();
        painter.setPen(QPen(Qt::red, 2));
        painter.rotate(6.0 * time.second());
        painter.drawLine(0, 0, 0, -85);
        painter.restore();
    }
};


#endif //PROGETTO_TIMER_ANALOGCLOCK_H