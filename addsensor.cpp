#include "addsensor.h"
#include "ui_addsensor.h"
#include "sensor.h"
#include "QString"
#include "filemanager.h"
#include "mainwindow.h"

AddSensor::AddSensor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSensor)
{
    ui->setupUi(this);



    mw = static_cast<MainWindow*>(parent);
    if (mw == nullptr){
        qErrnoWarning("No Parent");
    }

    PinsLineEdits = QVector<QLineEdit*>{};


    InitializeSensors();

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


    clearLayout(ui->PinsLayout);

    PinsLineEdits.clear();

    int Row = 0;
    for (Pin pin : VerfuegbareSensoren.at(ui->comboBox->currentIndex()).GetPins()){
        QLabel* NamePin = new QLabel;
        QLineEdit* NumberPin = new QLineEdit;

        PinsLineEdits.push_back(NumberPin);

        NumberPin->setValidator(new QIntValidator(0,20,this));

        NamePin->setText(pin.Description);
        NumberPin->setText(QString::number(pin.PinNummer));

        ui->PinsLayout->addWidget(NamePin,Row,0);
        ui->PinsLayout->addWidget(NumberPin,Row,1);
        Row++;
    }


}

void AddSensor::InitializeSensors()
{
    FileManager fm;

    QString ProjectPath =  static_cast<QString>(PROJECT_PATH);

    VerfuegbareSensoren = QVector<Sensor>{
        //Photoresistor
        Sensor{
        ProjectPath + "/Images/Photoresitor.png",
        "Photoresistor",
        "",
        QVector<Pin>{{1,"OUTPUT"}},
        fm.GetCodeSnippetFromFile(ProjectPath + "/Files/LEDBUILTIN.txt")},
        //Ultrasonic module
        Sensor{
        ProjectPath + "/Images/Ultraschall.jpg",
        "Supersonic",
        "",
        QVector<Pin>{{1,"TRIGGER"},{2,"ECHO"}},
        fm.GetCodeSnippetFromFile(ProjectPath + "/Files/LEDBUILTIN.txt")
        },
        Sensor{
        ProjectPath + "/Images/PushButton.jpg",
        "Push Button",
        "",
        QVector<Pin>{{1,"OUTPUT"}},
        fm.GetCodeSnippetFromFile(ProjectPath + "/Files/LEDBUILTIN.txt")
        }


    };



}

void AddSensor::clearLayout(QLayout *layout)
{
    if (layout == NULL)
        return;
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}


void AddSensor::on_buttonBox_accepted()
{



    Sensor selectedSensor;

    int index = ui->comboBox->currentIndex();

    selectedSensor.SetIconFilePath(VerfuegbareSensoren.at(index).GetIconFilePath());
    selectedSensor.SetType(VerfuegbareSensoren.at(index).GetArt());
    selectedSensor.SetDescription(ui->DescriptionLineEdit->text());

    QVector<Pin> Pins{};
    int i = 0;
    for (QLineEdit* le : PinsLineEdits){

        QString Description;
        int PinNumber;

        Description = VerfuegbareSensoren.at(index).GetPins().at(i).Description;
        PinNumber = le->text().toInt();

        Pin pin = Pin{PinNumber,Description};
        Pins.push_back(pin);
        i++;
    }
    selectedSensor.SetPins(Pins);

    mw->AddSensorToGrid(selectedSensor);
}

