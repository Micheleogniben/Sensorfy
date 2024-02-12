#include "sensor.h"

Sensor::Sensor(std::string sensorName, std::string sensorDesc, std::string sensorId) : name(sensorName), desc(sensorDesc), id(sensorId) { };

Sensor::Sensor(Sensor& sensor) : name(sensor.name),  desc(sensor.desc), id(sensor.id) { };