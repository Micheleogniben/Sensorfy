#include "sensorlist.h"
#include "temperature.h"
#include "noise.h"
#include "wind.h"

#include <algorithm>

SensorList::SensorList() : head(nullptr), size(0) {}

SensorList::SensorList(const SensorList& other) : head(nullptr), size(0) {
    Node* current = other.head;

    while (current != nullptr) {
        Sensor* copiedSensor = nullptr;

        if (dynamic_cast<Noise*>(current->data))
            copiedSensor = new Noise(*(dynamic_cast<Noise*>(current->data)));
        else if (dynamic_cast<Wind*>(current->data))
            copiedSensor = new Wind(*(dynamic_cast<Wind*>(current->data)));
        else if (dynamic_cast<Temperature*>(current->data))
            copiedSensor = new Temperature(*(dynamic_cast<Temperature*>(current->data)));

        addSensor(copiedSensor);
        current = current->next;
    }
}

SensorList::~SensorList() {
    while (!isEmpty())
        pop();
}

Sensor* SensorList::operator[](unsigned int i) const {
    SensorList::Iterator it = begin();

    for (unsigned int j = 0; j < i && it != end(); ++j, ++it) { };

    return it != end() ? *it : nullptr;
}

Sensor* SensorList::get(unsigned int i) const {
    SensorList::Iterator it = begin();

    for (unsigned int j = 0; j < i && it != end(); ++j, ++it) { };

    return it != end() ? *it : nullptr;
}


SensorList::Iterator::Iterator(SensorList::Node* start) : current(start) {}

SensorList::Iterator SensorList::begin() const {
    return Iterator(head);
}

SensorList::Iterator SensorList::end() const {
    return Iterator(nullptr);
}

bool SensorList::Iterator::operator==(const Iterator& other) const {
    return current == other.current;
}

bool SensorList::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

SensorList::Iterator& SensorList::Iterator::operator++() {
    if (current)
        current = current->next;

    return *this;
}

Sensor* SensorList::Iterator::operator*() {
    if (current)
        return current->data;

    return nullptr; // Nessun elemento rimanente
}

bool SensorList::deleteByName(std::string name) {
    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->data->getName() == name) {
            // Trovato il sensore da eliminare
            if (previous == nullptr) {
                pop();
                return true;
            } else {
                // Il sensore da eliminare è in mezzo o alla fine della lista
                previous->next = current->next;
            }

            delete current;
            size--;
            return true;
        }

        previous = current;
        current = current->next;
    }

    return false; // sensore non trovato
}


void SensorList::pop() {
    if (!isEmpty()) {
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
    }
}

SensorList* SensorList::filterByName(const std::string& searchTerm) const {
    SensorList* filteredList = new SensorList();

    for (Iterator it = begin(); it != end(); ++it) {
        if ((*it)->getName().find(searchTerm) != std::string::npos) {
            filteredList->addSensor(*it);
        }
    }

    return filteredList;
}

Sensor* SensorList::getFront() const {
    if (!isEmpty())
        return head->data;

    return nullptr;
}


bool SensorList::isEmpty() const {
    return size == 0;
}

bool SensorList::isNameTaken(const std::string& name) const {
    for (Iterator it = begin(); it != end(); ++it) {
        if ((*it)->getName() == name) {
            return true;
        }
    }
    return false;
}

unsigned int SensorList::getSize() const {
    return size;
}

bool SensorList::addSensor(Sensor* data) {
    Node* newNode = new Node(data);
    newNode->next = nullptr;

    if (isNameTaken(data->getName()))
        return false;

    if (isEmpty()) {
        head = newNode;
    } else {
        Node* lastNode = head;
        while (lastNode->next != nullptr)
            lastNode = lastNode->next;

        lastNode->next = newNode;
    }

    size++;

    return true;
}
