#ifndef WIND_H
#define WIND_H

#include "sensor.h"

class Wind : public Sensor{
    public:
        Wind(std::string, std::string, std::string);
        const void generateData(unsigned short) const override;
        const void showChart() const override;
    private:
        std::vector<float> measurements;
};

#endif