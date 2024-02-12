#ifndef SENSOR_LIST_H
#define SENSOR_LIST_H

#include "sensor.h"

class SensorList {
public:
    SensorList();
    SensorList(const SensorList&);
    ~SensorList();

    Sensor* getFront() const;
    Sensor* findByName(std::string&) const;

    void pop();
    bool deleteByName(std::string&);
    bool addSensor(Sensor*);

    bool isEmpty() const;
    bool isNameTaken(std::string&);

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
    Iterator& operator--();
    void operator++(int);

private:
    Node* current;
};


#endif // SENSOR_LIST_H