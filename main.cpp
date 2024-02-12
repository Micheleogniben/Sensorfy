// #include <QApplication>

// #include "mainwindow.h"
#include "sensor.h"
#include "temperature.h"
#include "wind.h"
#include "sound.h"
#include "sensorList.h"

int main(int argc, char *argv[])
{
    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    SensorList* sensors = new SensorList();

    sensors->addSensor(new Temperature("", "", ""));
    sensors->addSensor(new Wind("", "", ""));
    sensors->addSensor(new Sound("", "", ""));

    for (auto it = sensors->begin() ; it != sensors->end() ; ++it) {
        (*it).generateData(12);
        (*it).showChart();
    }

    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    return 0;//a.exec();
}