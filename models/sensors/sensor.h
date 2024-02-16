#ifndef SENSOR_H
#define SENSOR_H

#include <string>

#include <QJsonObject>
#include <QJsonDocument>
#include <QRandomGenerator>

#include "controller.h"

class Sensor{
public:
    Sensor(std::string&, std::string&, std::string&, std::string);
    Sensor(std::string&, std::string&, std::string);
    Sensor(Sensor&);

    virtual void generateData(unsigned short) =0;
    virtual const std::string toJson() const = 0;
    virtual void showChart(Controller*) const =0;
    virtual const unsigned short getNumMis() const =0;

    std::string getName() const;
    std::string getDesc() const;
    std::string getId() const;
    const std::string getIcon() const;

    void setName(const std::string&);
    void setDesc(const std::string&);

    static std::string generateUniqueId();

private:
    std::string name, desc, id;
    const std::string iconName;
};

#endif
