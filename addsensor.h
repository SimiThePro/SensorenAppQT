#ifndef ADDSENSOR_H
#define ADDSENSOR_H

#include <QDialog>
#include "sensor.h"

namespace Ui {
class AddSensor;
}

class AddSensor : public QDialog
{
    Q_OBJECT

public:
    explicit AddSensor(QWidget *parent = nullptr);
    ~AddSensor();

private slots:
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::AddSensor *ui;

    QStringList Sensoren;

    void InitializeSensors();

    void clearLayout(QLayout *layout);
};

inline QVector<class Sensor> VerfuegbareSensoren;

#endif // ADDSENSOR_H
