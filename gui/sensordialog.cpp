#include "sensordialog.h"

#include <QtCharts>

#include <QMessageBox>

SensorDialog::SensorDialog(Controller* c, Sensor *s, QWidget *parent) : QDialog(parent), sensor(s), controller(c)
{
    setupUi(s);
}

void SensorDialog::setupUi(Sensor *sensor)
{

    nameLabel = new QLabel(QString::fromStdString(sensor->getName()));
    nameLabel->setStyleSheet("font-size: 24px; font-weight: bold;");

    idLabel = new QLabel(QString::fromStdString(sensor->getId()));
    idLabel->setStyleSheet("font-size: 12px;");

    descLabel = new QLabel(QString::fromStdString(sensor->getDesc()));
    descLabel->setStyleSheet("font-size: 18px;");

    // Layout setup
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(nameLabel);
    layout->addWidget(idLabel);
    layout->addWidget(descLabel);

    // Aggiunta dei pulsanti
    QHBoxLayout *buttonLayout = new QHBoxLayout();  // Layout per i pulsanti
    QPushButton *editBtn = new QPushButton("Modifica Nome");
    QPushButton *editDescBtn = new QPushButton("Modifica Descrizione"); // Pulsante per la modifica della descrizione
    QPushButton *simulateBtn = new QPushButton("Simulate");

    editBtn->setStyleSheet("QPushButton {"
                                "    font-size: 20px;"
                                "    border-radius: 10px;"
                                "    border: 2px solid #4B4B4B;"
                                "}");

    editDescBtn->setStyleSheet("QPushButton {"
                                "    font-size: 20px;"
                                "    border-radius: 10px;"
                                "    border: 2px solid #4B4B4B;"
                                "}");

    simulateBtn->setStyleSheet("QPushButton {"
                                "    font-size: 20px;"
                                "    border-radius: 10px;"
                                "    border: 2px solid #4B4B4B;"
                                "}");

    // Connessione dei pulsanti ai rispettivi slot
    connect(editBtn, &QPushButton::clicked, this, &SensorDialog::editNameBtnClicked);
    connect(editDescBtn, &QPushButton::clicked, this, &SensorDialog::editDescBtnClicked);
    connect(simulateBtn, &QPushButton::clicked, this, &SensorDialog::simulateBtnClicked);

    buttonLayout->addWidget(simulateBtn);
    buttonLayout->addWidget(editBtn);
    buttonLayout->addWidget(editDescBtn); // Aggiungi il pulsante "Modifica Descrizione" al layout
    layout->addLayout(buttonLayout);  // Aggiunta del layout dei pulsanti al layout principale

    setFixedSize(800, 500);

    setLayout(layout);
}

void SensorDialog::addChartView(QChartView* chartView){
    // Assicurati che il puntatore alla finestra principale non sia nullo
    if (chartView) {
        // Memorizza il widget del grafico
        this->chartView = chartView;

        // Aggiungi la vista del grafico al layout della finestra di dialogo
        QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(this->layout());
        if (layout)
            layout->addWidget(chartView);
    }
}

void SensorDialog::addWidgetView(QWidget* widgetView) {
    // Assicurati che il puntatore alla finestra principale non sia nullo
    if (!widgetView)
        return;

    this->listWidget = widgetView;

    // Aggiungi la vista del widget al layout della finestra di dialogo
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(this->layout());
    if (layout)
        layout->addWidget(widgetView);
}


void SensorDialog::editNameBtnClicked(){
    QString newName = QInputDialog::getText(this, tr("Modifica nome sensore"), tr("Inserisci un nuovo nome:"), QLineEdit::Normal, nameLabel->text());
    if (!newName.isEmpty()) {
        nameLabel->setText(newName);
        sensor->setName(newName.toStdString());
    }
}

void SensorDialog::editDescBtnClicked(){
    QString newDesc = QInputDialog::getText(this, tr("Modifica descrizione sensore"), tr("Inserisci una nuova descrizione:"), QLineEdit::Normal, descLabel->text());
    if (!newDesc.isEmpty()) {
        descLabel->setText(newDesc);
        sensor->setDesc(newDesc.toStdString());
    }
}

void SensorDialog::simulateBtnClicked(){
    // Chiedi all'utente il numero di misurazioni da simulare
    bool ok;

    int numMeasurements = QInputDialog::getInt(
        this,
        tr("Simulazione"),
        tr("Inserisci il numero di misurazioni da simulare:"),
        sensor->getNumMis(),
        0,
        1024,
        1,
        &ok);

    // Se l'utente ha premuto "OK" e il numero di misurazioni è maggiore di 0, procedi con la simulazione
    if (ok && numMeasurements >= 0 && numMeasurements <= 1024) {
        sensor->generateData(numMeasurements);
        sensor->showChart(controller);
    }
}

void SensorDialog::removeChartView() {
    if (chartView) {

        // Rimuovi la vista del grafico dal layout e rilascia la memoria
        QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(this->layout());
        if (layout) {
            layout->removeWidget(chartView);
            delete chartView;
            chartView = nullptr;
        }
    }
}

void SensorDialog::removeListWidget() {
    // Assicurati che il QListWidget sia valido
    if (listWidget) {
        // Rimuovi il QListWidget dal layout e rilascia la memoria
        QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(this->layout());
        if (layout) {
            layout->removeWidget(listWidget);
            delete listWidget;
            listWidget = nullptr;
        }
    }
}

