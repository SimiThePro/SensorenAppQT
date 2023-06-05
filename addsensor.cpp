#include "addsensor.h"
#include "qmessagebox.h"
#include "qpushbutton.h"
#include "qspinbox.h"
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

    QString UsedDigitalPinsText = "";
    for (int pinnumber : UsedDigitalPins){
        UsedDigitalPinsText.append(QString::number(pinnumber) + ",");
    }
    ui->UsedDigitalPins->setText(UsedDigitalPinsText);
    QString UsedAnalogPinsText = "";
    for (int pinnumber : UsedAnalogPins){
        UsedAnalogPinsText.append(QString::number(pinnumber) + ",");
    }
    ui->UsedAnalogPins->setText(UsedAnalogPinsText);

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

        if (pin.isAnalogPin){
            /*
            NumberPin->setPlaceholderText("A");
            NumberPin->setInputMask("A9");
            connect(NumberPin, &QLineEdit::textEdited, [=](){QString text = NumberPin->text();

                // If the text is empty or doesn't start with "A", reset it to "A"
                if (text.isEmpty() || !text.startsWith("A")) {
                    NumberPin->setText("A");
                    NumberPin->setCursorPosition(1); // Set the cursor position after "A"
                }
                // If the text is longer than "A" followed by a single digit, truncate it
                else if (text.length() > 2) {
                    NumberPin->setText(text.left(2));
                    NumberPin->setCursorPosition(1); // Set the cursor position after "A"
                }


        });

        NumberPin->setText("A" + QString::number(pin.PinNummer));
        */

        }


        NumberPin->setValidator(new QIntValidator(0,20,this));





        NamePin->setText(pin.Description + (pin.isAnalogPin == true ? " (A)" : ""));
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
        QVector<Pin>{{1,"OUTPUT",true}},
        QVector<ValueMeasure>{{"Resistance"}},
        QVector<MeasureSetting>{
            {"Interval",QVariant::fromValue(new QSpinBox)},
            {"Test",QVariant::fromValue(new QLineEdit)}
            }
        },
        //Ultrasonic module
        Sensor{
        ProjectPath + "/Images/Ultraschall.jpg",
        "Supersonic",
        "",
        QVector<Pin>{{1,"TRIGGER"},{2,"ECHO"}},
        QVector<ValueMeasure>{{"Distance"}}
        },
        Sensor{
        ProjectPath + "/Images/PushButton.jpg",
        "Push Button",
        "",
        QVector<Pin>{{1,"OUTPUT"}},
        QVector<ValueMeasure>{{"Status"}}
        },
        Sensor{
        ProjectPath + "/Images/Thermistor.jpg",
            "Thermistor",
            "",
            QVector<Pin>{{1,"OUTPUT"}},
            QVector<ValueMeasure>{{"Temperature"}}
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






    int index = ui->comboBox->currentIndex();

    Sensor selectedSensor = VerfuegbareSensoren.at(index);

    selectedSensor.SetDescription(ui->DescriptionLineEdit->text());

    QVector<Pin> Pins{};
    int i = 0;

    for(int i=0;i<PinsLineEdits.size();i++)
    {
        for(int j=i+1;j<PinsLineEdits.size();j++)
        {
            // comparing array elements
            if(PinsLineEdits[i]->text()==PinsLineEdits[j]->text())
            {
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setText("Can't enter the same Pins");
                msgBox.exec();
                return;
            }
        }
    }

    for (QLineEdit* le : PinsLineEdits){

        QString Description;
        int PinNumber;

        Description = VerfuegbareSensoren.at(index).GetPins().at(i).Description;
        PinNumber = le->text().toInt();

        if (VerfuegbareSensoren.at(index).GetPins().at(i).isAnalogPin){
            if (UsedAnalogPins.contains(PinNumber)){
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setText("Pin is already in use");
                msgBox.exec();
                return;
            }

        }else{
            if (UsedDigitalPins.contains(PinNumber)) {
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setText("Pin is already in use");
                msgBox.exec();
                return;
            }

        }

        Pin pin = Pin{PinNumber,Description,VerfuegbareSensoren.at(index).GetPins().at(i).isAnalogPin};
        Pins.push_back(pin);
        i++;
    }
    selectedSensor.SetPins(Pins);



    mw->AddSensorToGrid(selectedSensor);
}

