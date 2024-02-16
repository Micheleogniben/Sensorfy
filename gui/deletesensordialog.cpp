#include "deletesensordialog.h"
#include <QVBoxLayout>
#include <QPushButton>

DeleteSensorDialog::DeleteSensorDialog(const QStringList &sensorNames, QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Elimina sensore");

    QVBoxLayout *layout = new QVBoxLayout(this);

    sensorComboBox = new QComboBox;
    sensorComboBox->addItems(sensorNames);

    QHBoxLayout *buttonLayout = new QHBoxLayout;

    QPushButton *deleteButton = new QPushButton("OK");
    QPushButton *cancelButton = new QPushButton("Annulla");

    connect(deleteButton, &QPushButton::clicked, this, &DeleteSensorDialog::deleteSensor);
    connect(cancelButton, &QPushButton::clicked, this, &DeleteSensorDialog::reject);

    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(cancelButton);

    layout->addWidget(sensorComboBox);
    layout->addLayout(buttonLayout);

    setLayout(layout);
}


void DeleteSensorDialog::deleteSensor()
{
    QString sensorName = sensorComboBox->currentText();
    emit sensorDeleted(sensorName);
    accept();
}

