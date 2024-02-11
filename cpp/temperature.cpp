#include "temperature.h"
#include <random>
#include <iostream>

Temperature::Temperature(std::string name, std::string desc, std::string id) : Sensor(name, desc, id) { };

const void Temperature::generateData(unsigned short n) {
    // Generatore random di tipo Mersenne Twister necessario alla creazione di una curva gaussiana
    std::random_device rd;
    std::mt19937 gen(rd());

    // Parametri per la simulazione della temperatura
    const float minVal = 15.0,
        maxVal = 30.0,
        hourPick = 14.0,
        standardDev = 2.0;
    
    float measure = 0.0, 
        hour = 0.0;

    for (int i = 0; i < n; i++) {
        // Calcolo della temperatura per l'i-esima misura usando una distribuzione normale
        hour = 24.0f / n * i;
        measure = minVal + (maxVal - minVal) *
                            std::exp(-0.5f * std::pow((hour - hourPick) / standardDev, 2));

        // Aggiungiamo un po' di rumore casuale per rendere i dati più realistici
        std::normal_distribution<float> distribuzione_rumore(0.0f, 1.0f);
        measure += distribuzione_rumore(gen);

        this->measurements.push_back(measure);
    }
}

const void Temperature::showChart() const {
    for (int i = 0; i < measurements.size(); ++i)
        std::cout << "ora" << 24.0f / measurements.size() * i << ": " << measurements[i];
}