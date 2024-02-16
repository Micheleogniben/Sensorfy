#ifndef NOISE_H
#define NOISE_H

#include "sensor.h"
#include <vector>
#include <map>

class Noise : public Sensor{
public:
    Noise(std::string, std::string, std::string);
    Noise(std::string, std::string);
    Noise(Noise&);

    void generateData(unsigned short) override;
    const std::string toJson() const override;
    void showChart(Controller*) const override;
    const unsigned short getNumMis() const override;

private:
    std::vector<float> measurements;
};

#endif
