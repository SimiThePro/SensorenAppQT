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

    void on_buttonBox_accepted();

private:
    Ui::AddSensor *ui;

    QStringList Sensoren;

    void InitializeSensors();

    void clearLayout(QLayout *layout);

    class MainWindow* mw;

    QVector<class QLineEdit*> PinsLineEdits;
};

inline QVector<class Sensor> VerfuegbareSensoren;
inline QVector<class Sensor> CurrentSensors;
inline QVector<int> UsedPins{};

#endif // ADDSENSOR_H
