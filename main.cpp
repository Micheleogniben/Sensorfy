// #include <QApplication>

// #include "mainwindow.h"
#include "sensor.h"
#include "temperature.h"
#include "wind.h"
#include "sound.h"

int main(int argc, char *argv[])
{
    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    Sensor* s1 = new Temperature("", "", "");
    Sensor* s2 = new Wind("", "", "");
    Sensor* s3 = new Sound("", "", "");

    s1->generateData(48);
    s2->generateData(48);
    s3->generateData(48);

    s1->showChart();
    s2->showChart();
    s3->showChart();

    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    return 0;//a.exec();
}