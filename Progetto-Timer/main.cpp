#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QDateTime>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;

    //Finestra
    window.resize(300, 400);
    window.setWindowTitle("Timer");

    //Label per il timer digitale
    QLabel digitalTimeLabel(&window);
    digitalTimeLabel.setAlignment(Qt::AlignCenter);
    digitalTimeLabel.setGeometry(0, 0, 200,50);
    digitalTimeLabel.setStyleSheet("font-size: 24px;");

    digitalTimeLabel.setText("");


    window.show();
    return app.exec();
}