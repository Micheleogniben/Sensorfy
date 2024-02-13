#include "sensorList.h"
#include "temperature.h"
#include "noise.h"
#include "wind.h"

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

bool SensorList::deleteByName(std::string& name) {
    Node* current = head;
    Node* previous = nullptr;

    if (findByName(name) != nullptr){
        while (current != nullptr) {
            std::string currentName = current->data->getName();
            std::transform(currentName.begin(), currentName.end(), currentName.begin(), ::tolower); // convertire il nome del sensore in minuscolo
            if (currentName == name) {
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


Sensor* SensorList::findByName(const std::string& name) const {
    std::string lowerCase = name; // convertire il nome del sensore in minuscolo
    std::transform(lowerCase.begin(), lowerCase.end(), lowerCase.begin(), ::tolower); // convertire il nome del sensore in minuscolo

    Node* current = head;
    std::string currentName;
    while (current != nullptr) {
        currentName = current->data->getName();
        std::transform(currentName.begin(), currentName.end(), currentName.begin(), ::tolower); // convertire il nome del sensore in minuscolo

        if (currentName.compare(name) == 0) {
            return current->data;
        }
        current = current->next;
    }
    return nullptr; // sensore non trovato
}


Sensor* SensorList::getFront() const {
    if (!isEmpty())
        return head->data;

    return nullptr;
}


bool SensorList::isEmpty() const {
    return size == 0;
}

bool SensorList::isNameTaken(const std::string& name) const{
    return findByName(name) != nullptr;
}

unsigned int SensorList::getSize() const {
    return size;
}

bool SensorList::addSensor(Sensor* data) {
    Node* newNode = new Node(data);
    newNode->next = nullptr;

    if (!isNameTaken(newNode->data->getName())){    
        if (isEmpty()) {
            head = newNode;
        } else {
                Node* lastNode = head;
                while (lastNode->next != nullptr)
                    lastNode = lastNode->next;

                lastNode->next = newNode;
            }

        size++;
    }

    return true;
}