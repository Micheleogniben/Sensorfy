#include "sensor.h"

Sensor::Sensor(std::string& sensorName, std::string& sensorDesc, std::string& sensorId, std::string icon)
    : name(sensorName), desc(sensorDesc), id(sensorId), iconName(icon) { }

Sensor::Sensor(std::string& sensorName, std::string& sensorDesc, std::string icon)
    : name(sensorName), desc(sensorDesc), id(Sensor::generateUniqueId()), iconName(icon) { }

Sensor::Sensor(Sensor& sensor) : name(sensor.name),  desc(sensor.desc), id(sensor.id) { }

std::string Sensor::getName() const{ return this->name; }

std::string Sensor::getDesc() const { return this->desc; }

std::string Sensor::getId() const { return this->id; }

const std::string Sensor::getIcon() const { return this->iconName; }

void Sensor::setName(const std::string& str) { this->name = str; }

void Sensor::setDesc(const std::string& str) { this->desc = str; }

std::string Sensor::generateUniqueId() {
    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    const int randomStringLength = 10; // Lunghezza della stringa di caratteri random

    QString randomString;
    for(int i = 0; i < randomStringLength; ++i) {
        int index = QRandomGenerator::global()->bounded(possibleCharacters.length());
        QChar nextChar = possibleCharacters.at(index);
        randomString.append(nextChar);
    }

    return randomString.toStdString();
}
