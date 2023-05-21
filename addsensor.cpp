#include "addsensor.h"
#include "ui_addsensor.h"

AddSensor::AddSensor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSensor)
{
    ui->setupUi(this);




    QPixmap pix("C:\\Users\\simim\\Documents\\QT\\Personal\\SensorenApp\\Images\\Photoresitor.png");
    ui->label->setPixmap(pix.scaled(200,200,Qt::KeepAspectRatio));
}

AddSensor::~AddSensor()
{
    delete ui;
}
