
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

#define _STR(x) #x
#define STR(x) _STR(x)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    fm(new FileManager)

{
    ui->setupUi(this);



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

    Serial* serial = new Serial;


    connect(serial,&Serial::MessageReceived,this,&MainWindow::MessageReceived);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::Compiling()
{

    arguments.clear();
    arguments << "compile" << "--fqbn" << "arduino:avr:uno" << Ino_Location << "-v";
    Compile->startDetached(CLI_Location,arguments);
    Compile->close();

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
        Row++;
    }






    Row = 0;
    for (Pin pin : sensor.GetPins()){
        QLabel* NamePin = new QLabel;
        QLabel* NumberPin = new QLabel;

        NamePin->setText(pin.Description);
        NumberPin->setText(QString::number(pin.PinNummer));

        SensorUi->PinsGrid->addWidget(NamePin,Row,0);
        SensorUi->PinsGrid->addWidget(NumberPin,Row,1);
        Row++;
    }






    SensorWidget->setMaximumSize(200,500);
    ui->Sensoren->addWidget(SensorWidget,0,ui->Sensoren->columnCount()+1);

    CurrentSensors.push_back(sensor);



    for (Pin pin : sensor.GetPins()){
        UsedPins.push_back(pin.PinNummer);
    }

    for (int i = 0; i < UsedPins.length(); i++){
        qInfo() << UsedPins.at(i);
    }




}

void MainWindow::Uploading()
{

    qWarning() << "Uploading";
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

    //CodeSnippet snippet = fm->GetCodeSnippetFromFile(static_cast<QString>(PROJECT_PATH) + "Files/LEDBUILTIN.txt");
    //fm->AddCodeSnippetToIno(snippet);
    //Uploading();
    //fm->RemoveCodeSnippet(snippet);


    AddSensor* sensor = new AddSensor(this);
    sensor->show();


}

void MainWindow::MessageReceived(QString Message)
{


    if (Message.contains(':')){
        qInfo() << Message.sliced(Message.indexOf(':')+1);

        if (CurrentSensors.at(0).GetArt() == "Photoresistor"){

            for (int i=0; i < CurrentSensors.at(0).GetUi()->MessungenGrid->count(); ++i) {
                QLayoutItem *item = CurrentSensors.at(0).GetUi()->MessungenGrid->itemAt(i);
                if (!item || !item->widget())
                    continue;
                QLabel *label = qobject_cast<QLabel*>(item->widget());
                if (label) {
                    if (i == 1){
                        label->setText( Message.sliced(Message.indexOf(':')+1) + "Ω");
                    }
                }
            }

        }
    }


    if (Message == "Pressed"){



    }else if (Message == "Released");

}



