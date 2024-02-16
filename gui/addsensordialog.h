// addsensorialog.h
#ifndef ADDSENSORDIALOG_H
#define ADDSENSORDIALOG_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QComboBox;

class AddSensorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSensorDialog(QWidget *parent = nullptr);

signals:
    void sensorAdded(QString type, QString name, QString description);

private slots:
    void addSensor();

private:
    QLabel *typeLabel;
    QComboBox *typeComboBox;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QLabel *descriptionLabel;
    QLineEdit *descriptionLineEdit;
    QPushButton *addButton;
    QPushButton *cancelButton;
};

#endif // ADDSENSORDIALOG_H
