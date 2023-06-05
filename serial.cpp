#include "serial.h"
#include "QSerialPort"
#include "QMessageBox"
#include "QProcess"
#include "QTimer"

Serial::Serial(QObject *parent)
    : QObject{parent},
    mSerial(new QSerialPort),
    bShouldRead(false)
{
    connect(mSerial,&QSerialPort::readyRead, this, &Serial::ReadyRead);

    //OpenSerialPort();


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
    mSerial->setPortName("COM4");
    mSerial->setBaudRate(QSerialPort::Baud9600);
    mSerial->setDataBits(QSerialPort::Data8);
    mSerial->setParity(QSerialPort::NoParity);
    mSerial->setStopBits(QSerialPort::OneStop);
    mSerial->setFlowControl(QSerialPort::NoFlowControl);

    if (mSerial->open(QIODevice::ReadWrite)) {
        qInfo() << "Succesfully connected";
    }

}

void Serial::ReadyRead()
{
    QByteArray data = mSerial->readAll();

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
    if (UploadOutput.contains("Das Maximum sind")){
        QTimer::singleShot(4000,this,&Serial::OpenSerialPort);
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
