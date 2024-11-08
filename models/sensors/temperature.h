#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "sensor.h"
#include <vector>

class Temperature : public Sensor{
public:
    Temperature(std::string, std::string, std::string);
    Temperature(std::string, std::string);
    Temperature(Temperature&);

    void generateData(unsigned short) override;
    const std::string toJson() const override;
    void showChart(Controller*) const override;
    const unsigned short getNumMis() const override;

private:
    std::vector<float> measurements;
};

#endif
