#include "sensorbutton.h"
#include <QLabel>
#include <QVBoxLayout>

#include "sensorbutton.h"
#include "sensordialog.h"
#include "controller.h"

SensorButton::SensorButton(Sensor *s, QWidget *parent) : QPushButton(parent), sensor(s)
{
    setFixedSize(140, 140);

    // Crea un layout verticale per il pulsante
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Crea un QLabel per il testo del pulsante e aggiungilo al layout
    QLabel *textLabel = new QLabel(QString::fromStdString(sensor->getName()), this);
    textLabel->setAlignment(Qt::AlignHCenter | Qt::AlignBottom); // Opzionale: regola l'allineamento
    textLabel->size();
    textLabel->setStyleSheet("font-size: 15px; font-weight: bold; color: black;");
    layout->addWidget(textLabel); // Aggiunge il testo al layout

    // Imposta l'icona del pulsante sopra il testo
    QIcon icon(":/res/" + QString::fromStdString(sensor->getIcon()) + ".png");
    setIcon(icon);
    setIconSize(QSize(70, 70));
    setStyleSheet("QPushButton { border-radius: 20px; background-color: #BEBEBE; }");

    // Connetti il segnale clicked() del pulsante alla tua funzione di slot
    connect(this, &QPushButton::clicked, this, &SensorButton::handleClick);
}

void SensorButton::handleClick()
{
    Controller* controller = new Controller();
    SensorDialog dialog(controller, sensor, this);
    controller->setSensorDialog(&dialog);
    sensor->showChart(controller);

    dialog.exec();
}


SensorButton::~SensorButton()
{
    // Deallocazione della memoria per eventuali risorse se necessario
}
