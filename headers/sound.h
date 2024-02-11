#ifndef SOUND_H
#define SOUND_H

#include "sensor.h"
#include <vector>
#include <map>

class Sound : public Sensor{
    public:
        Sound(std::string, std::string, std::string);
        const void generateData(unsigned short) override;
        const void showChart() const override;
    private:
        std::vector<float> measurements;
};

#endif