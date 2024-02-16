#ifndef SENSORBUTTON_H
#define SENSORBUTTON_H

#include <QPushButton>

#include "sensor.h"

class SensorButton : public QPushButton
{
    Q_OBJECT

public:
    explicit SensorButton(Sensor* sensor, QWidget *parent = nullptr);
    ~SensorButton();

signals:
    void clicked();

private:
    Sensor* sensor;
    void handleClick();
};

#endif // SENSORBUTTON_H
