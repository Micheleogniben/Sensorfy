#ifndef PARSER_H
#define PARSER_H

#include "sensorlist.h"

class Parser
{
public:
    SensorList* loadSensorList(const std::string&);
    void saveJson(const std::string&, const SensorList*);
};

#endif // PARSER_H
