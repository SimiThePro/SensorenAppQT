#include "serial.h"
#include "QSerialPort"
#include "QMessageBox"
#include "QProcess"
#include "QTimer"
#include "QSerialPort"
#include "QSerialPortInfo"

Serial::Serial(QObject *parent)
    : QObject{parent},
    mSerial(new QSerialPort),
    bShouldRead(false)
{
    connect(mSerial,&QSerialPort::readyRead, this, &Serial::ReadyRead);

    //OpenSerialPort();


    for (const QSerialPortInfo &serialPortInfo : QSerialPortInfo::availablePorts()){

        if (serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if (serialPortInfo.vendorIdentifier() == 9025){
                if(serialPortInfo.productIdentifier() == 67){
                    ArduinoPort = serialPortInfo.portName();
                    qInfo() << "Arduino Uno found";
                }
            }
        }
    }

    CLI = new QProcess;
    Compile = new QProcess;
    Upload = new QProcess;
    CLI_Location = "C:/Users/simim/Documents/Arduino-CLI/arduino-cli.exe";

    Ino_Location = static_cast<QString>(PROJECT_PATH) + "Sketch";

    UploadOutput = "";

}

void Serial::OpenSerialPort()
{
    Upload->close();
    qInfo() << "Opening";
    mSerial->setPortName(ArduinoPort);
    mSerial->setBaudRate(QSerialPort::Baud9600);
    mSerial->setDataBits(QSerialPort::Data8);
    mSerial->setParity(QSerialPort::NoParity);
    mSerial->setStopBits(QSerialPort::OneStop);
    mSerial->setFlowControl(QSerialPort::NoFlowControl);

    if (mSerial->open(QIODevice::ReadWrite)) {
        qInfo() << "Succesfully connected";
    }else{
        qInfo() << mSerial->errorString();
    }

}

void Serial::ReadyRead()
{
    QByteArray data = mSerial->readAll();

    qInfo() << data;

    for (int i = 0; i < data.size(); i++) {
        char receivedChar = data.at(i);

        if (receivedChar == '#') {
            // Start marker found, clear the previous message data
            Message.clear();
            bShouldRead = true;
        } else if (receivedChar == '*') {
            // End marker found, process the received message
            if (bShouldRead) {
                emit MessageReceived(Message);
                bShouldRead = false;
            }
        } else if (bShouldRead) {
            // Add the received character to the message data
            Message.append(receivedChar);
        }
    }


}

void Serial::ReadProcess()
{
    UploadOutput = Upload->readAllStandardOutput();
    qInfo() << UploadOutput;
    if (UploadOutput.contains("\\Local\\Arduino15\\packages\\arduino\\hardware\\avr\\1.8.6\u001B[0m")){
        QTimer::singleShot(500,this,&Serial::OpenSerialPort);
    }
}

void Serial::Compiling()
{
    arguments.clear();
    arguments << "compile" << "--fqbn" << "arduino:avr:uno" << Ino_Location << "-v";
    Compile->startDetached(CLI_Location,arguments);
}

void Serial::Uploading()
{

    mSerial->close();

    qInfo() << "Uploading";
    arguments.clear();
    arguments << "compile" << "--upload" << "--port" << "COM4" << "--fqbn" << "arduino:avr:uno" << Ino_Location;
    Upload->start(CLI_Location,arguments,QIODeviceBase::ReadOnly);

    QObject::connect(Upload,SIGNAL(readyReadStandardOutput()),this,SLOT(ReadProcess()));



    //OpenSerialPort();
}
