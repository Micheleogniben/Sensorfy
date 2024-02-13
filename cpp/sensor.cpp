#include "sensor.h"

Sensor::Sensor(std::string& sensorName, std::string& sensorDesc, std::string& sensorId) 
                : name(sensorName), desc(sensorDesc), id(sensorId) { };

Sensor::Sensor(Sensor& sensor) : name(sensor.name),  desc(sensor.desc), id(sensor.id) { };

std::string Sensor::getName() const{ return this->name; }

std::string Sensor::getDesc() const { return this->desc; }

std::string Sensor::getId() const { return this->id; }

void Sensor::setName(const std::string& str) { this->name = str; }

void Sensor::setDesc(const std::string& str) { this->desc = str; }