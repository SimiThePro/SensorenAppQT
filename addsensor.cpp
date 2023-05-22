#include "addsensor.h"
#include "ui_addsensor.h"
#include "QString"

AddSensor::AddSensor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSensor)
{
    ui->setupUi(this);




    QPixmap pix(static_cast<QString>(PROJECT_PATH) + "\\Images\\Photoresitor.png");
    ui->label->setPixmap(pix.scaled(200,200,Qt::KeepAspectRatio));
}

AddSensor::~AddSensor()
{
    delete ui;
}
