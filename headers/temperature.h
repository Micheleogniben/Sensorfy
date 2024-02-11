#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "sensor.h"

class Temperature : public Sensor{
    public:
        Temperature(std::string, std::string, std::string);
        const void generateData(unsigned short) const override;
        const void showChart() const override;
    private:
        std::vector<float> measurements;
};

#endif