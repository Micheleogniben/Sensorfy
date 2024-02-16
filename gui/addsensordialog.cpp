// addsensorialog.cpp
#include "addsensordialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QMessageBox>

AddSensorDialog::AddSensorDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Aggiungi sensore");

    QVBoxLayout *layout = new QVBoxLayout(this);

    typeLabel = new QLabel("Tipo di sensore:");
    typeComboBox = new QComboBox;
    typeComboBox->addItem("Wind");
    typeComboBox->addItem("Noise");
    typeComboBox->addItem("Temperature");

    nameLabel = new QLabel("Nome:");
    nameLineEdit = new QLineEdit;

    descriptionLabel = new QLabel("Descrizione:");
    descriptionLineEdit = new QLineEdit;

    addButton = new QPushButton("Aggiungi");
    cancelButton = new QPushButton("Annulla");

    connect(addButton, &QPushButton::clicked, this, &AddSensorDialog::addSensor);
    connect(cancelButton, &QPushButton::clicked, this, &AddSensorDialog::reject);

    layout->addWidget(typeLabel);
    layout->addWidget(typeComboBox);
    layout->addWidget(nameLabel);
    layout->addWidget(nameLineEdit);
    layout->addWidget(descriptionLabel);
    layout->addWidget(descriptionLineEdit);
    layout->addWidget(addButton);
    layout->addWidget(cancelButton);

    setLayout(layout);
}

void AddSensorDialog::addSensor()
{
    QString type = typeComboBox->currentText();
    QString name = nameLineEdit->text();
    QString description = descriptionLineEdit->text();

    if (name.isEmpty() || description.isEmpty()) {
        QMessageBox::warning(this, "Errore", "Per favore, compila tutti i campi.");
        return;
    }

    emit sensorAdded(type, name, description);
    accept();
}

