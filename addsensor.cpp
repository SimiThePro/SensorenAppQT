#include "addsensor.h"
#include "ui_addsensor.h"
#include "sensor.h"
#include "QString"
#include "filemanager.h"

AddSensor::AddSensor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSensor)
{
    ui->setupUi(this);

    FileManager fm;

    QString ProjectPath =  static_cast<QString>(PROJECT_PATH);

    QVector<Pin>{{1,"OUTPUT"},{2,"TRIGGER"}};

    VerfuegbareSensoren.push_back(Sensor{
         ProjectPath + "/Images/Photoresitor.png",
         "Photoresistor",
         "",
         QVector<Pin>{{1,"OUTPUT"}},
         fm.GetCodeSnippetFromFile(ProjectPath + "/Files/LEDBUILTIN.txt")});

    VerfuegbareSensoren.push_back(Sensor{
        ProjectPath + "/Images/Ultraschall.jpg",
        "Supersonic",
        "",
        QVector<Pin>{{1,"TRIGGER"},{2,"ECHO"}},
        fm.GetCodeSnippetFromFile(ProjectPath + "/Files/LEDBUILTIN.txt")
    });


    for (Sensor sensor : VerfuegbareSensoren){
        Sensoren.push_back(sensor.GetArt());
    }

    ui->comboBox->addItems(Sensoren);

    QPixmap pix(static_cast<QString>(PROJECT_PATH) + "\\Images\\Photoresitor.png");
    ui->label->setPixmap(pix.scaled(200,200,Qt::KeepAspectRatio));
}

AddSensor::~AddSensor()
{
    delete ui;
}

void AddSensor::on_comboBox_currentIndexChanged(int index)
{
    QPixmap pix(VerfuegbareSensoren.at(index).GetIconFilePath());
    ui->label->setPixmap(pix.scaled(200,200,Qt::KeepAspectRatio));
}

