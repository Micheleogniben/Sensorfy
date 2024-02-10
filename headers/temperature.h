#include "sensor.h"

class Temperature : public Sensor{
    public:
        Temperature(std::string, std::string, std::string);
        const std::vector<float> generateData(unsigned short) const override;
};