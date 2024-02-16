#ifndef SENSORDIALOG_H
#define SENSORDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QWidget>
#include <QChartView>
#include <QLineSeries>

#include "sensor.h"
#include "controller.h"

class Sensor;

class SensorDialog : public QDialog
{
    Q_OBJECT
public:
    SensorDialog(Controller*, Sensor*, QWidget* = nullptr);
    void addChartView(QChartView*);
    void addWidgetView(QWidget*);

    void removeChartView();
    void removeListWidget();

private:
    QLabel *nameLabel;
    QLabel *idLabel;
    QLabel *descLabel;

    QChartView *chartView = nullptr;
    QWidget* listWidget = nullptr;

    void setupUi(Sensor *sensor);
    void editNameBtnClicked();
    void editDescBtnClicked();
    void simulateBtnClicked();

    Sensor* sensor;
    Controller* controller;
};

#endif
