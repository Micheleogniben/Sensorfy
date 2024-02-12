#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "sensor.h"
#include <vector>

class Temperature : public Sensor{
    public:
        Temperature(std::string, std::string, std::string);
        void generateData(unsigned short) override;
        void showChart() const override;
    private:
        std::vector<float> measurements;
};

#endif