#include "wind.h"
#include <random>
#include <cmath>

Wind::Wind(std::string name, std::string desc, std::string id) : Sensor(name, desc, id, "wind") { }
Wind::Wind(std::string name, std::string desc) : Sensor(name, desc, "wind") { }

Wind::Wind(Wind& sensor) : Sensor(sensor), measurements(sensor.measurements) { }

void Wind::generateData(unsigned short n) {

    measurements.clear();

    // Generatore random di tipo Mersenne Twister necessario alla creazione di una curva gaussiana
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> windSpeed(0.0f, 30.0f);
    std::uniform_int_distribution<unsigned short> windDirection(0, 359);
    std::tuple<unsigned short, float> misurazione;

    for (unsigned short i = 0; i < n; i++)
        this->measurements.push_back({round(windSpeed(gen) * 100) / 100, windDirection(gen)});
}

void Wind::showChart(Controller* controllerPtr) const {
    if (controllerPtr)
        controllerPtr->addWidgetListToDialog(measurements);
}

const std::string Wind::toJson() const {
    QJsonObject jsonObject;
    jsonObject["type"] = "Wind";
    jsonObject["name"] = QString::fromStdString(getName());
    jsonObject["desc"] = QString::fromStdString(getDesc());
    jsonObject["id"] = QString::fromStdString(getId());
    // Aggiungi ulteriori campi specifici per Wind, come le misurazioni

    QJsonDocument jsonDoc(jsonObject);
    return jsonDoc.toJson(QJsonDocument::Compact).toStdString();
}

const unsigned short Wind::getNumMis() const {
    return measurements.size();
}
