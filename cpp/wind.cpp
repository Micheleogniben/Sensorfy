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

    for (unsigned short i = 0; i < n; i++)
        this->measurements.push_back({windDirection(gen), windSpeed(gen)});

    //TODO: trasformare il metodo: lui calcola a prescindere ogni ora e nel caso l'utente chieda intervalli strani
    //TODO: si crea un algoritmo che calcoli la media e trova nell'intervallo dei due dati cosa ci sarebbe stato
    
    //TODO: ovviamente se la differenza tra mis1 e mis2 è minore di 180 si fa la media giusta, altrimenti
    //TODO: si  deve fare un'interpolazione per trovare il valore corretto in mezzo. (dal lato sinistro)

    //TODO: magari aggiungere anche un po' di rumore ai dati, quindi non la media perfetta, ma sporcata
}

const void Wind::showChart() const {

}