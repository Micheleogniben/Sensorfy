#ifndef WIND_H
#define WIND_H

#include "sensor.h"
#include <vector>
#include <tuple>

class Wind : public Sensor{
    public:
        Wind(std::string, std::string, std::string);
        Wind(Wind&);
        void generateData(unsigned short) override;
        void showChart() const override;
    private:
        std::vector<std::tuple<float, unsigned short>> measurements;
};

#endif