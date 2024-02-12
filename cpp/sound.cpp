#include "sound.h"
#include <random>

Sound::Sound(std::string name, std::string desc, std::string id) : Sensor(name, desc, id) { };

Sound::Sound(Sound& sensor) : Sensor(sensor), measurements(sensor.measurements) { };

void Sound::generateData(unsigned short n) {
    // Definisci un generatore di numeri casuali
    std::random_device rd;
    std::mt19937 gen(rd());

    // distribuzioni del rumore per diverse fasce orarie
    std::uniform_int_distribution<> night(30, 50); // Rumore di notte
    std::normal_distribution<> morning(50, 10); // Rumore al mattino
    std::normal_distribution<> afternoon(70, 15); // Rumore al pomeriggio
    std::normal_distribution<> evening(60, 10); // Rumore alla sera
    unsigned int measure = 0;
    float hour = 0;

    for (unsigned short i = 0; i < n; ++i) {
        // calcolo l'ora in cui si trova l'i-esima misurazione
        hour = 24.0f / n * i;

        // la distribuzione del rumore varia in base all'ora del giorno
        if (hour >= 6 && hour < 12) {
            measure = morning(gen);
        } else if (hour >= 12 && hour < 18) {
            measure = afternoon(gen);
        } else if (hour >= 18 && hour < 22) {
            measure = evening(gen);
        } else {
            measure = night(gen);
        }

        if ((hour >= 6 && hour < 9) || (hour >= 17 && hour < 19)) {
            measure += 15; // Picco di traffico durante l'ora di punta del mattino e della sera
        } else if (hour >= 22 || hour < 5) {
            measure -= 10; // Riduzione del rumore durante la notte
        }

        // check per verificare che i db siano tra 0 e 100
        this->measurements.push_back(measure);
    }
}

#include <iostream>
void Sound::showChart() const {
    for  (int i = 0; i < measurements.size(); i++) {
        std::cout<<"ora "<<24 / measurements.size() * i<<": "<<measurements[i]<<std::endl;
    }
}