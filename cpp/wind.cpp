#include "wind.h"
#include <random>

Wind::Wind(std::string name, std::string desc, std::string id) : Sensor(name, desc, id) { };

const void Wind::generateData(unsigned short n) {
    // Generatore random di tipo Mersenne Twister necessario alla creazione di una curva gaussiana
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> windSpeed(0.0f, 30.0f);
    std::uniform_int_distribution<unsigned short> windDirection(0, 359);
    std::tuple<unsigned short, float> misurazione;

    for (int ora = 0; ora < n; ora++)
        this->measurements.push_back({windDirection(gen), windSpeed(gen)});
}

const void Wind::showChart() const {

}