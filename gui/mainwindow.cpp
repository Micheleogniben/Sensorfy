#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sensorbutton.h"
#include "addsensordialog.h"
#include "deletesensordialog.h"

#include "wind.h"
#include "noise.h"
#include "temperature.h"
#include "controller.h"
#include "parser.h"
#include "sensordialog.h"

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

#include <QDir>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Alloca e configura la scroll area
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setAlignment(Qt::AlignCenter);
    setCentralWidget(scrollArea);

    sensors = new SensorList();

    startScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startScreen()
{
    setWindowTitle("Sensorfy");
    setFixedSize(600, 300);

    mainLayout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("BENVENUTO IN SENSORFY");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 32px; font-weight: bold;");

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *createButton = new QPushButton("Inizia sessione");
    createButton->setFixedSize(200, 50);
    createButton->setStyleSheet("QPushButton {"
                                "    font-size: 20px;"
                                "    border-radius: 10px;"
                                "    border: 2px solid #4B4B4B;"
                                "}");

    QPushButton *loadButton = new QPushButton("Carica sessione");
    loadButton->setFixedSize(200, 50);
    loadButton->setStyleSheet("QPushButton {"
                              "    font-size: 20px;"
                              "    border-radius: 10px;"
                              "    border: 2px solid #4B4B4B;"
                              "}");

    connect(createButton, &QPushButton::clicked, this, [&]() {
        loadSensorScreen(sensors);
    });

    connect(loadButton, &QPushButton::clicked, this, [&]() {
        try {
            QString filePath = QFileDialog::getOpenFileName(
                this,
                "Seleziona un file",
                QDir::homePath(),
                "File JSON (*.json)"
                );

            if (filePath.isEmpty())
                throw std::runtime_error("Percorso non selezionato!");

            sensors = (new Parser())->loadSensorList(filePath.toStdString());
            loadSensorScreen(sensors);
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Errore", "C'è stato un errore nel caricamento dei sensori: " + QString(e.what()));
        }
    });

    buttonLayout->addWidget(createButton);
    buttonLayout->addWidget(loadButton);

    mainLayout->addStretch(1);
    mainLayout->addWidget(titleLabel);
    mainLayout->addStretch(1);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch(1);

    QWidget* central = centralWidget();
    if (central->layout()) {
        QLayout* existingLayout = central->layout();
        central->setLayout(nullptr);
        delete existingLayout;
    }

    central->setLayout(mainLayout);

    show();
}

void MainWindow::loadSensorScreen(SensorList* s) {
    // Imposta la dimensione massima possibile per consentire il ridimensionamento
    setFixedSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);

    // Imposta la dimensione minima della finestra
    setMinimumSize(650, 450);

    QLineEdit *searchLineEdit = new QLineEdit();

    // Crea e configura la scroll area
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    // Crea il widget contenitore per la schermata dei sensori
    QWidget *sensorWidget = new QWidget();
    scrollArea->setWidget(sensorWidget);

    // Crea il layout verticale principale per il widget contenitore
    mainLayout = new QVBoxLayout(sensorWidget);
    mainLayout->setAlignment(Qt::AlignTop);

    // Aggiungi la barra di ricerca e i pulsanti
    // Crea il layout orizzontale per la barra di ricerca
    QHBoxLayout *searchLayout = new QHBoxLayout();

    // Crea i widget per la barra di ricerca
    QLabel *searchLabel = new QLabel("Cerca:");
    searchLineEdit->setPlaceholderText("Inserisci il termine di ricerca...");
    QPushButton *searchButton = new QPushButton("Cerca");

    connect(searchButton, &QPushButton::clicked, this, [=]() {
        QString searchTerm = searchLineEdit->text();
        addSensorsToScreen(sensors->filterByName(searchTerm.toStdString()));
    });

    // Aggiungi i widget al layout della barra di ricerca
    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(searchLineEdit);
    searchLayout->addWidget(searchButton);

    // Crea i pulsanti per aggiungere, eliminare e salvare i sensori
    QPushButton *addBtn = new QPushButton("Aggiungi sensore");
    QPushButton *delBtn = new QPushButton("Elimina sensore");
    QPushButton *saveBtn = new QPushButton("Salva lista");

    // Connessioni dei segnali e dei slot per i pulsanti
    connect(addBtn, &QPushButton::clicked, this, &MainWindow::addSensor);
    connect(delBtn, &QPushButton::clicked, this, &MainWindow::deleteSensor);
    connect(saveBtn, &QPushButton::clicked, this, &MainWindow::saveSensorList);

    // Aggiungi i pulsanti al layout
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(addBtn);
    btnLayout->addWidget(delBtn);
    btnLayout->addWidget(saveBtn);

    // Aggiungi i layout alla schermata principale
    mainLayout->addLayout(searchLayout);
    mainLayout->addLayout(btnLayout);
    mainLayout->addStretch(1);  // Aggiungi uno stretch per allineare i widget in alto

    // Aggiungi i sensori alla schermata
    addSensorsToScreen(s);

    // Rimuovi il layout e i widget precedenti
    QWidget *previousWidget = centralWidget();
    setCentralWidget(scrollArea);
    delete previousWidget;
}

void MainWindow::addSensorsToScreen(SensorList* s) {
    QHBoxLayout* sensorRowLayout = nullptr;

    for (auto& sensorButton : sensorButtons)
        delete sensorButton;

    sensorButtons.clear();

    // Itera sui sensori filtrati e aggiungili alla schermata
    for (unsigned short k = 0; k < s->getSize(); ++k) {
        // Se siamo all'inizio di una nuova riga, crea un nuovo layout orizzontale
        if (k % 4 == 0) {
            sensorRowLayout = new QHBoxLayout();
            mainLayout->addLayout(sensorRowLayout);
            mainLayout->addStretch(1);
        }

        // Crea e aggiungi il pulsante del sensore al layout della riga
        Sensor* sensor = s->get(k);
        SensorButton *sensorButton = new SensorButton(sensor);
        sensorButtons.push_back(sensorButton);
        sensorRowLayout->addWidget(sensorButton);
    }
}

void MainWindow::saveSensorList() {
    try {
        // Ottieni il percorso del file JSON in cui salvare i sensori
        QString filePath = QFileDialog::getSaveFileName(
            this,
            "Salva lista di sensori",
            QDir::homePath(),
            "File JSON (*.json)"
            );

        if (filePath.isEmpty())
            throw std::runtime_error("Percorso non selezionato!");

        // Salva la lista dei sensori nel file JSON
        (new Parser())->saveJson(filePath.toStdString(), sensors);
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Errore", "C'è stato un errore nel salvataggio dei sensori: " + QString(e.what()));
    }
}


void MainWindow::addSensor() {
    // Crea un'istanza del dialogo di aggiunta sensore
    AddSensorDialog dialog(this);

    // Connetti il segnale sensorAdded del dialogo a uno slot del MainWindow
    connect(&dialog, &AddSensorDialog::sensorAdded, this, &MainWindow::handleSensorAdded);

    // Mostra il dialogo
    dialog.exec();
}

void MainWindow::handleSensorAdded(QString type, QString name, QString description) {
    Sensor *newSensor = nullptr;

    if (type == "Wind")
        newSensor = new Wind(name.toStdString(), description.toStdString());
    else if (type == "Noise")
        newSensor = new Noise(name.toStdString(), description.toStdString());
    else if (type == "Temperature")
        newSensor = new Temperature(name.toStdString(), description.toStdString());

    if (newSensor && sensors->addSensor(newSensor)) {
        addSensorsToScreen(sensors); // Ricarica la schermata dei sensori dopo la rimozione
    } else {
        QMessageBox::warning(this, "Errore", "Impossibile aggiungere il sensore. Verifica i dati inseriti.");
    }
}

void MainWindow::deleteSensor() {
    // Creare una lista di nomi dei sensori
    QStringList sensorNames;
    for (unsigned short k = 0; k < sensors->getSize(); ++k) {
        sensorNames << QString::fromStdString(sensors->get(k)->getName());
    }

    // Ottenere il nome del sensore da eliminare
    QString sensorName = QInputDialog::getItem(this, "Elimina sensore", "Seleziona il sensore da eliminare:", sensorNames, 0, false);

    // Verificare se il nome del sensore è valido
    if (!sensorName.isEmpty()) {

        // Eliminare direttamente il sensore dal sensorelist
        sensors->deleteByName(sensorName.toStdString());

        addSensorsToScreen(sensors); // Ricarica la schermata dei sensori dopo la rimozione
    }
}
