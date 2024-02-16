######################################################################
# Automatically generated by qmake (3.1) Thu Feb 15 21:01:19 2024
######################################################################

TEMPLATE = app
TARGET = Sensorify
INCLUDEPATH += controller \
               gui \
               models \
               models/sensors

QT += core gui widgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_UP_TO=0x060000 # disables all APIs deprecated in Qt 6.0.0 and earlier

# Input
HEADERS += controller/controller.h \
           controller/parser.h \
           gui/addsensordialog.h \
           gui/deletesensordialog.h \
           "gui/mainwindow copia.h" \
           gui/mainwindow.h \
           gui/sensorbutton.h \
           gui/sensordialog.h \
           models/sensorlist.h \
           models/sensors/noise.h \
           models/sensors/sensor.h \
           models/sensors/temperature.h \
           models/sensors/wind.h
FORMS += gui/mainwindow.ui
SOURCES += main.cpp \
           controller/controller.cpp \
           controller/parser.cpp \
           gui/addsensordialog.cpp \
           gui/deletesensordialog.cpp \
           "gui/mainwindow copia.cpp" \
           gui/mainwindow.cpp \
           gui/sensorbutton.cpp \
           gui/sensordialog.cpp \
           models/sensorlist.cpp \
           models/sensors/noise.cpp \
           models/sensors/sensor.cpp \
           models/sensors/temperature.cpp \
           models/sensors/wind.cpp
RESOURCES += gui/res.qrc
