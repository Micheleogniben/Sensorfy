TEMPLATE = app
TARGET = MyProject

QT += core gui widgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += main.cpp

# Include header and source files from the others directory
INCLUDEPATH += $$PWD/headers
HEADERS += \
    headers/sensor.h \
    headers/sensorList.h \
    headers/sound.h \
    headers/temperature.h \
    headers/wind.h \

SOURCES += \
    cpp/sensor.cpp \
    cpp/sensorList.cpp \
    cpp/sound.cpp \
    cpp/temperature.cpp \
    cpp/wind.cpp \

# RESOURCES += \
#     resources.qrc
# 
# DISTFILES += \
#     Resources/knight.png