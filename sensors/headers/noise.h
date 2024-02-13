#ifndef SOUND_H
#define SOUND_H

#include "sensor.h"
#include <vector>
#include <map>

class Noise : public Sensor{
    public:
        Noise(std::string, std::string, std::string);
        Noise(Noise&);
        void generateData(unsigned short) override;
        void showChart() const override;
    private:
        std::vector<float> measurements;
};

#endif