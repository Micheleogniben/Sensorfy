#include "wind.h"
#include <random>

Wind::Wind(std::string name, std::string desc, std::string id) : Sensor(name, desc, id) { };

const void Wind::generateData(unsigned short n) {
    // Inizializza il generatore di numeri casuali
    std::random_device rd;
    std::mt19937 gen(rd());

    // Definisci le distribuzioni per la velocità e la direzione del vento
    std::uniform_real_distribution<float> distribuzione_velocita(0.0f, 30.0f); // Supponiamo vento fino a 30 m/s
    std::uniform_int_distribution<unsigned short> distribuzione_direzione(0, 359); // Direzione del vento in gradi (0-359)

    // Simula le misurazioni per ogni ora
    for (int ora = 0; ora < n; ora++) {
        // Mappa per contenere le misurazioni per questa ora
        std::tuple<unsigned short, float> misurazione;

        // Genera una misurazione di velocità e direzione del vento
        float velocita = distribuzione_velocita(gen);
        unsigned short direzione = distribuzione_direzione(gen);

        // Aggiungi la misurazione alla mappa
        misurazione = {direzione, velocita};

        // Aggiungi la mappa al vettore di misurazioni
        measurements.push_back(misurazione);
    }
}

const void Wind::showChart() const {

}