#ifndef ADDSENSOR_H
#define ADDSENSOR_H

#include <QDialog>

namespace Ui {
class AddSensor;
}

class AddSensor : public QDialog
{
    Q_OBJECT

public:
    explicit AddSensor(QWidget *parent = nullptr);
    ~AddSensor();

private:
    Ui::AddSensor *ui;

    QStringList Sensoren;
};

#endif // ADDSENSOR_H
