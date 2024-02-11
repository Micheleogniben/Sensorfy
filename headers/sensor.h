#ifndef SENSOR_H
#define SENSOR_H

#include <string>

class Sensor{
    public:
        Sensor(std::string, std::string, std::string);
        virtual const void generateData(unsigned short) =0;
        virtual const void showChart() const =0;
    private:
        std::string name, desc, id;
};

#endif