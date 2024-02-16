#ifndef SENSOR_LIST_H
#define SENSOR_LIST_H

#include "sensor.h"
#include <iostream>

class SensorList {
public:
    SensorList();
    SensorList(const SensorList&);
    ~SensorList();

    Sensor* getFront() const;

    void pop();
    bool deleteByName(std::string);
    bool addSensor(Sensor*);

    bool isEmpty() const;
    bool isNameTaken(const std::string&) const;
    SensorList* filterByName(const std::string& searchTerm) const;

    Sensor* operator[](unsigned int) const;
    Sensor* get(unsigned int) const;

    unsigned int getSize() const;


    class Iterator;

    Iterator begin() const;
    Iterator end() const;

private:
    struct Node {
        Sensor* data;
        Node* next;

        Node(Sensor* d) : data(d), next(nullptr) {}
    };

    Node *head;
    unsigned int size;
};


class SensorList::Iterator {
public:
    Iterator(Node* start);

    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;
    Iterator& operator++();
    Sensor* operator*();

private:
    Node* current;
};


#endif // SENSOR_LIST_H
