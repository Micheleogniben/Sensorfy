#include "sensor.h"

class Humidity : public Sensor{
    public:
        Humidity(std::string, std::string, std::string);
        const std::vector<float> generateData(unsigned short) const override;
};