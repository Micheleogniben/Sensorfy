#include <QApplication>

#include "mainwindow.h"
#include "sensor.h"
#include "temperature.h"
#include "wind.h"
#include "sound.h"
#include "sensorList.h"
#include <iostream>

int main(int argc, char *argv[])
{
    SensorList* sensors = new SensorList();

    sensors->addSensor(new Temperature("", "", ""));
    sensors->addSensor(new Wind("d", "", ""));
    sensors->addSensor(new Sound("f", "", ""));

    for (SensorList::Iterator it = sensors->begin(); it != sensors->end(); ++it) {
        (*it)->generateData(24);
        (*it)->showChart();
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
