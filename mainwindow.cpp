
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QProcess"
#include "QtSerialPort/QSerialPort"
#include "QtSerialPort/QSerialPortInfo"
#include "QDebug"
#include "QDir"
#include "QElapsedTimer"
#include "QEventLoop"
#include "filemanager.h"
#include "addsensor.h"
#include "ui_Sensor.h"
#include "QLabel"
#include "QLineEdit"
#include "serial.h"
#include "QSpinBox"

#define _STR(x) #x
#define STR(x) _STR(x)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);


    fm = new FileManager(this);

    auto SerialPorts = QSerialPortInfo::availablePorts();
    for (QSerialPortInfo Port : SerialPorts){
        Ports.append(Port.portName() + " " + Port.description());
    }
    ui->COMSelect->addItems(Ports);

    CLI = new QProcess;
    Compile = new QProcess;
    Upload = new QProcess;
    CLI_Location = "C:/Users/simim/Documents/Arduino CLI/bin/arduino-cli.exe";

    Ino_Location = static_cast<QString>(PROJECT_PATH) + "Sketch";

    InitializeArduino();


    CurrentSensors = QVector<Sensor>{};

    serial = new Serial;


    connect(serial,&Serial::MessageReceived,this,&MainWindow::MessageReceived);
}

MainWindow::~MainWindow()
{
    for (CodeSnippet snippet : CodeSnippets){
        FileManager::RemoveCodeSnippet(snippet);
    }

    delete ui;
}



void MainWindow::Compiling()
{

    arguments.clear();
    arguments << "compile" << "--fqbn" << "arduino:avr:uno" << Ino_Location << "-v";
    Compile->startDetached(CLI_Location,arguments);
    Compile->close();

}

void MainWindow::NeedToCompile(bool need)
{
    if (need){
        ui->CompileButton->setStyleSheet("background-color: red");
    }else{
        ui->CompileButton->setStyleSheet("background-color: green");
    }
}

void MainWindow::AddSensorToGrid(Sensor sensor)
{
    QWidget* SensorWidget = new QWidget;


    Ui::Sensor* SensorUi = new Ui::Sensor();
    SensorUi->setupUi(SensorWidget);

    sensor.SetUi(SensorUi);


    SensorUi->label->setPixmap(QPixmap(sensor.GetIconFilePath()).scaled(100,100,Qt::KeepAspectRatio));

    SensorUi->TypeLabel->setText(sensor.GetArt());

    SensorUi->DescriptionLabel->setText(sensor.GetDescription());

    int Row = 0;
    for (ValueMeasure measure : sensor.GetMeasures()){
        QLabel* DescriptionLabel = new QLabel();
        QLabel* ValueLabel = new QLabel;
        DescriptionLabel->setText(measure.Description);
        ValueLabel->setText("0");


        SensorUi->MessungenGrid->addWidget(DescriptionLabel,Row,0);
        SensorUi->MessungenGrid->addWidget(ValueLabel,Row,1);

        ValueLables.push_back(ValueLabel);

        Row++;
    }

    Row = 0;
    for (Pin pin : sensor.GetPins()){
        QLabel* NamePin = new QLabel;
        QLabel* NumberPin = new QLabel;

        NamePin->setText(pin.Description + (pin.isAnalogPin == true ? " (A)" : ""));
        NumberPin->setText(QString::number(pin.PinNummer));

        SensorUi->PinsGrid->addWidget(NamePin,Row,0);
        SensorUi->PinsGrid->addWidget(NumberPin,Row,1);
        Row++;
    }


    Row = 0;
    if (sensor.GetMeasureSettings().size() == 0){
        delete SensorUi->label_2;
        delete SensorUi->horizontalLayout_4;
    }
    else{
    for (MeasureSetting setting : sensor.GetMeasureSettings()){
        QLabel* NamePin = new QLabel;

        NamePin->setText(setting.Description);

        if (setting.variant.canConvert<QLineEdit*>()){
            QLineEdit* lineEdit = setting.variant.value<QLineEdit*>();

            lineEdit->setText(0);

            connect(lineEdit, &QLineEdit::textChanged,this,&MainWindow::handleTextChanged);

            SensorUi->SettingsGrid->addWidget(lineEdit,Row,1);

        }else if (setting.variant.canConvert<QDoubleSpinBox*>()){
            QDoubleSpinBox* spinBox = setting.variant.value<QDoubleSpinBox*>();
            spinBox->setValue(0);


            connect(spinBox, &QDoubleSpinBox::textChanged,this,&MainWindow::handleTextChanged);

            SensorUi->SettingsGrid->addWidget(spinBox,Row,1);
        }

        SensorUi->SettingsGrid->addWidget(NamePin,Row,0);
        Row++;
    }
    }




    SensorWidget->setMaximumSize(200,500);
    ui->Sensoren->addWidget(SensorWidget,0,ui->Sensoren->columnCount()+1);

    fm->SetupFileForSensor(sensor);
    CurrentSensors.push_back(sensor);





    for (Pin pin : sensor.GetPins()){
        if (pin.isAnalogPin)
            UsedAnalogPins.push_back(pin.PinNummer);
        else
        UsedDigitalPins.push_back(pin.PinNummer);
    }

    NeedToCompile(true);

}

void MainWindow::Uploading()
{

    qInfo() << "Uploading";
    arguments.clear();

    arguments << "compile" << "--upload" << "--port" << "COM3" << "--fqbn" << "arduino:avr:uno" << Ino_Location;

    Upload->startDetached(CLI_Location,arguments);
}


void MainWindow::InitializeArduino()
{
    QString Output;

    /*
    arguments.clear();
    arguments << "config" << "init" << "--overwrite";
    CLI->startDetached(CLI_Location,arguments);
    CLI->close();
    arguments.clear();
    arguments << "sketch" << "new" << Ino_Location;
    CLI->startDetached(CLI_Location,arguments);
    CLI->close();

    arguments.clear();
    arguments << "core" << "update-index";
    CLI->startDetached(CLI_Location,arguments);
    CLI->close();


    arguments.clear();
    arguments << "board" << "list";
    CLI->startDetached(CLI_Location,arguments);
    while (CLI->canReadLine()){
        Output += CLI->readLine();
    }

    CLI->close();
    */
}


void MainWindow::on_pushButton_2_clicked()
{

    AddSensor* addsensor = new AddSensor(this);
    addsensor->exec();


}

void MainWindow::MessageReceived(QString Message)
{



    int index = 0;

    if (Message.contains(';') && Message.contains(':')){
        QVector<QString> Messages{};
        while (Message.contains(';')){
            QString SlicedMessage = Message.sliced(0,Message.indexOf(';'));
            Messages.push_back(SlicedMessage);
            Message.remove(0,Message.indexOf(';')+1);
        }

        for (const QString &message : Messages){

            if (message == "") continue;
            index = static_cast<QString>(message.at(0)).toInt();

            if (ValueLables.size() <= index) return;

            if (ValueLables.at(index) == nullptr) continue;

            ValueLables.at(index)->setText(message.sliced(message.indexOf(':')+1));
        }

        /*

        qInfo() << Message.sliced(Message.indexOf(':')+1);

        if (CurrentSensors.size() <= index) return;

        */




        /*
        for (int i=0; i < CurrentSensors.at(index).GetUi()->MessungenGrid->count(); ++i) {
            QLayoutItem *item = CurrentSensors.at(index).GetUi()->MessungenGrid->itemAt(i);
            if (!item || !item->widget())
                continue;
            QLabel *label = qobject_cast<QLabel*>(item->widget());
            if (label) {
                if (i == 1){
                    label->setText( Message.sliced(Message.indexOf(':')+1));
                }
            }
        }
        */

    }



}




void MainWindow::on_CompileButton_clicked()
{
    NeedToCompile(false);
    serial->Uploading();
}

void MainWindow::handleTextChanged(const QString &newText)
{
    QObject* senderObject = QObject::sender();
    int sensorindex = 0;
    int settingindex = 0;
    for (Sensor sensor : CurrentSensors){
        settingindex = 0;
        for (MeasureSetting setting : sensor.GetMeasureSettings()){
            if (setting.variant.value<QLineEdit*>() == senderObject || setting.variant.value<QDoubleSpinBox*>() == senderObject){
                qInfo() << CurrentSensors.at(sensorindex).GetMeasureSettings().at(settingindex).VariableName;

                fm->SettingChanged(CurrentSensors.at(sensorindex).GetMeasureSettings().at(settingindex).VariableName,newText);
            }
            settingindex++;
        }
        sensorindex++;
    }



}

