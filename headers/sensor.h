#ifndef SENSOR_H
#define SENSOR_H

#include <string>

class Sensor{
    public:
        Sensor(std::string&, std::string&, std::string&);
        Sensor(Sensor&);
        virtual void generateData(unsigned short) =0;
        virtual void showChart() const =0;
        
        std::string getName() const;
        std::string getDesc() const;
        std::string getId() const;

        void setName(const std::string&);
        void setDesc(const std::string&);

    private:
        std::string name, desc, id;
};

#endif