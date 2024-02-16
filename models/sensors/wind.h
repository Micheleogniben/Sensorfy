#ifndef WIND_H
#define WIND_H

#include "sensor.h"
#include <vector>
#include <tuple>

class Wind : public Sensor{
public:
    Wind(std::string, std::string, std::string);
    Wind(std::string, std::string);
    Wind(Wind&);

    void generateData(unsigned short) override;
    const std::string toJson() const override;
    void showChart(Controller*) const override;
    const unsigned short getNumMis() const override;

private:
    std::vector<std::tuple<float, unsigned short>> measurements;
};

#endif
