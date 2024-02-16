#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class SensorDialog;

class Controller : public QObject {
    Q_OBJECT
public:
    Controller();
    void setSensorDialog(SensorDialog*);
    void generateChart(const std::vector<float>&);
    void addWidgetListToDialog(const std::vector<std::tuple<float, unsigned short>>&);

private:
    SensorDialog* dialogPtr;
};

#endif
