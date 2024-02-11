#ifndef WIND_H
#define WIND_H

#include "sensor.h"
#include <vector>
#include <map>

class Wind : public Sensor{
    public:
        Wind(std::string, std::string, std::string);
        const void generateData(unsigned short) override;
        const void showChart() const override;
    private:
        std::vector<std::map<float, unsigned short>> measurements;
};

#endif