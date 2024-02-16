#include "controller.h"
#include "sensordialog.h"

#include <QtCharts>
#include <algorithm>

Controller::Controller() : dialogPtr(nullptr) {}

void Controller::setSensorDialog(SensorDialog* dialog) {
    dialogPtr = dialog;
}

void Controller::generateChart(const std::vector<float>& data) {

    if (dialogPtr) {
        //trovo il valore massimo misurato dal sensore
        float maxValue = std::numeric_limits<float>::min();

        for (float value : data)
            maxValue = std::max(maxValue, value);

        // Creare una serie per il grafico
        QLineSeries *series = new QLineSeries();
        for (int i = 0; i < data.size(); ++i) {
            // Mappa l'indice i all'intervallo 0-24 sull'asse x
            // Assumendo che data.size() rappresenti 24 ore
            float x = static_cast<float>(i) * 24.0 / data.size();
            series->append(x, data[i]);
        }

        // Creare il grafico e aggiungere la serie
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Sensor Data");

        // Creare l'asse x con i valori da 0 a 24
        QValueAxis *axisX = new QValueAxis;
        axisX->setRange(0, 23);
        axisX->setLabelFormat("%d");
        axisX->setTickCount(25);
        chart->addAxis(axisX, Qt::AlignBottom);

        series->attachAxis(axisX);


        QValueAxis *axisY = new QValueAxis;
        axisY->setRange(0, maxValue + 5);
        axisY->setTickCount(10);
        chart->addAxis(axisY, Qt::AlignLeft);

        // Associare l'asse y alla serie
        series->attachAxis(axisY);

        chart->legend()->setVisible(false);

        // Creare una vista per il grafico
        QChartView *chartView = new QChartView(chart);

        // Aggiungere la vista del grafico al layout del dialogo
        SensorDialog* sensorDialog = dynamic_cast<SensorDialog*>(dialogPtr);
        if (sensorDialog) {
            sensorDialog->removeChartView();
            sensorDialog->addChartView(chartView);
        }
    }
}

void Controller::addWidgetListToDialog(const std::vector<std::tuple<float, unsigned short>>& data) {
    if (dialogPtr) {
        // Creazione di un'area di scorrimento verticale
        QScrollArea* scrollArea = new QScrollArea;
        scrollArea->setWidgetResizable(true);

        QWidget* widgetList = new QWidget;
        QVBoxLayout* mainLayout = new QVBoxLayout;
        widgetList->setLayout(mainLayout);
        scrollArea->setWidget(widgetList);

        // Creazione di un nuovo layout orizzontale per ogni riga
        QHBoxLayout* rowLayout = nullptr;

        // Tempo di inizio delle misurazioni
        QTime startTime(0, 0);

        // Intervallo tra le misurazioni in minuti
        int measurementInterval = 24.0f / data.size() * 60; // Supponiamo che ci sia una misurazione ogni 10 minuti

        // Aggiungi elementi alla lista
        for (size_t i = 0; i < data.size(); ++i) {
            float speed = std::get<0>(data[i]);
            // unsigned short direction = std::get<1>(data[i]);

            // Calcola l'ora della misurazione
            QTime measurementTime = startTime.addSecs(i * measurementInterval * 60);

            // Creazione del pulsante
            QToolButton* button = new QToolButton;
            button->setIcon(QIcon(":/res/wind.png"));
            button->setIconSize(QSize(64, 64));
            button->setText("Speed: " + QString::number(speed) + " m/s\nTime: " + measurementTime.toString("hh:mm"));
            button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
            button->setFixedSize(140, 140);
            button->setStyleSheet("QToolButton {"
                                      "border-radius: 20px; background-color: #BEBEBE; font-size: 15px; color: black;"
                                      "padding-top: 10px;" // Spazio sopra il testo
                                      "}"
                                      "QToolButton::icon {"
                                      "margin-bottom: 5px;" // Spazio sotto l'icona
                                      "}");

            // Aggiungi il pulsante al layout orizzontale corrente
            if (i % 5 == 0) {
                // Se è il primo elemento nella riga, crea un nuovo layout orizzontale
                rowLayout = new QHBoxLayout;
                mainLayout->addLayout(rowLayout);
            }
            rowLayout->addWidget(button);
        }

        // Aggiungi il widgetList al dialog
        SensorDialog* sensorDialog = dynamic_cast<SensorDialog*>(dialogPtr);
        if (sensorDialog) {
            sensorDialog->removeListWidget();
            sensorDialog->addWidgetView(scrollArea);
        }
    }
}
