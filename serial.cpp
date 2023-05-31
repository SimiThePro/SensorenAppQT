#include "serial.h"
#include "QSerialPort"
#include "QMessageBox"

Serial::Serial(QObject *parent)
    : QObject{parent},
    mSerial(new QSerialPort)
{
    connect(mSerial,&QSerialPort::readyRead, this, &Serial::ReadyRead);

    OpenSerialPort();
}

void Serial::OpenSerialPort()
{
    mSerial->setPortName("COM3");
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

    serialBuffer += QString::fromStdString(mSerial->readAll().toStdString());


    if (serialBuffer.contains('#'),serialBuffer.contains("*")){
        Message = serialBuffer.sliced(serialBuffer.indexOf('#')+1,(serialBuffer.indexOf('*')-1) - serialBuffer.indexOf('#'));
        serialBuffer.clear();
        emit MessageReceived(Message);
    }


}
