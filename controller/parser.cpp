#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>
#include <QFile>

#include "parser.h"
#include "noise.h"
#include "temperature.h"
#include "wind.h"
#include "sensorlist.h"

SensorList* Parser::loadSensorList(const std::string& filePath) {
    SensorList* sensorList = new SensorList();
    QFile file(QString::fromStdString(filePath));

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error("Error opening file for reading.");

    QTextStream stream(&file);
    QString jsonString = stream.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject sensorListObject = doc.object();

    QJsonArray sensorsArray = sensorListObject["sensors"].toArray();

    for (const QJsonValue& sensorValue : sensorsArray) {
        QJsonObject sensorObject = sensorValue.toObject();

        if (!sensorObject.contains("type") || !sensorObject.contains("name") || !sensorObject.contains("desc") || !sensorObject.contains("id"))
            throw std::runtime_error("Invalid JSON format: Missing required fields for character.");

        std::string type = sensorObject["type"].toString().toStdString();
        std::string name = sensorObject["name"].toString().toStdString();
        std::string desc = sensorObject["desc"].toString().toStdString();
        std::string id = sensorObject["id"].toString().toStdString();

        Sensor* sensor;

        if (type == "Wind")
            sensor = new Wind(name, desc, id);
        else if (type == "Noise")
            sensor = new Noise(name, desc, id);
        else if (type == "Temperature")
            sensor = new Temperature(name, desc, id);
        else
            throw std::runtime_error("Invalid character type.");

        sensorList->addSensor(sensor);
    }

    return sensorList;
}

void Parser::saveJson(const std::string& path, const SensorList* sensors) {
    QJsonObject sensorObject;
    QJsonArray sensorArray;

    for (SensorList::Iterator it = sensors->begin(); it != sensors->end(); ++it){
        QJsonDocument jsonDocument = QJsonDocument::fromJson(QByteArray::fromStdString((*it)->toJson()));

        if (!jsonDocument.isNull()) {
            if (jsonDocument.isObject()) {
                sensorArray.append(jsonDocument.object());
            } else {
                throw std::runtime_error("Errore nel parsing di un sensore, stringa non valida!");
            }
        } else {
            throw std::runtime_error("Errore nel parsing del QJsonDocument, stringa non valida!");
        }
    }

    sensorObject["sensors"] = sensorArray;

    QJsonDocument doc(sensorObject);
    QFile file(QString::fromStdString(path));

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        throw std::runtime_error("Errore durante l'apertura del file per il salvataggio.");

    QTextStream stream(&file);
    stream << doc.toJson();
    file.close();
}
