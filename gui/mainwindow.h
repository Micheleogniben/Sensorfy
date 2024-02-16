#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>

#include "ui_mainwindow.h"
#include "controller.h"
#include "parser.h"
#include "sensordialog.h"
#include "sensorlist.h"
#include "sensorbutton.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startScreen();
    void loadSensorScreen(SensorList* s);
    void addSensor();
    void handleSensorAdded(QString type, QString name, QString description);
    void deleteSensor();
    void saveSensorList();

private:
    Ui::MainWindow *ui;
    SensorList *sensors;
    QVBoxLayout *mainLayout = nullptr;
    QVector<SensorButton*> sensorButtons;

    void addSearchBarAndButtons();
    void addSensorsToScreen(SensorList* s);
};

#endif // MAINWINDOW_H
