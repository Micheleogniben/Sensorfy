#ifndef DELETESENSORDIALOG_H
#define DELETESENSORDIALOG_H

#include <QDialog>
#include <QComboBox>

class DeleteSensorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteSensorDialog(const QStringList &sensorNames, QWidget *parent = nullptr);

signals:
    void sensorDeleted(QString sensorName);

private slots:
    void deleteSensor();

private:
    QComboBox *sensorComboBox;
};

#endif // DELETESENSORDIALOG_H
