#include "temperature.h"
#include <random>

Temperature::Temperature(std::string name, std::string desc, std::string id) : Sensor(name, desc, id, "temp") { }
Temperature::Temperature(std::string name, std::string desc) : Sensor(name, desc, "temp") { }

Temperature::Temperature(Temperature& sensor) : Sensor(sensor), measurements(sensor.measurements) { }

void Temperature::generateData(unsigned short n) {

    measurements.clear();

    // Generatore random di tipo Mersenne Twister necessario alla creazione di una curva gaussiana
    std::random_device rd;
    std::mt19937 gen(rd());

    const float minVal = 15.0,
        maxVal = 30.0,
        hourPick = 14.0,
        standardDev = 2.0;

    float measure = 0.0,
        hour = 0.0;

    for (unsigned short i = 0; i < n; i++) {
        // calcolo l'ora in cui si trova l'i-esima misurazione
        hour = 24.0f / n * i;
        // Calcolo della temperatura per l'i-esima misura usando una distribuzione normale
        measure = minVal + (maxVal - minVal) *
                               std::exp(-0.5f * std::pow((hour - hourPick) / standardDev, 2));

        // Rumore casuale per rendere i dati più realistici
        std::normal_distribution<float> distribuzione_rumore(0.0f, 1.0f);
        measure += distribuzione_rumore(gen);

        this->measurements.push_back(measure);
    }
}

void Temperature::showChart(Controller* controllerPtr) const {
    if (controllerPtr)
        controllerPtr->generateChart(measurements);
}

const std::string Temperature::toJson() const {
    QJsonObject jsonObject;
    jsonObject["type"] = "Temperature";
    jsonObject["name"] = QString::fromStdString(getName());
    jsonObject["desc"] = QString::fromStdString(getDesc());
    jsonObject["id"] = QString::fromStdString(getId());
    // Aggiungi ulteriori campi specifici per Wind, come le misurazioni

    QJsonDocument jsonDoc(jsonObject);
    return jsonDoc.toJson(QJsonDocument::Compact).toStdString();
}


const unsigned short Temperature::getNumMis() const {
    return measurements.size();
}
