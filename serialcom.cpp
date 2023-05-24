#include "serialcom.h"
#include "qserialportinfo.h"
#include "QSerialPort"
#include "QSerialPortInfo"

SerialCOM::SerialCOM()
{

    auto SerialPorts = QSerialPortInfo::availablePorts();
    for (QSerialPortInfo Port : SerialPorts){
        Ports->append(Port.portName());
    }

    //mSerial = new QSerialPort(this);


    //connect(mSerial, &QSerialPort::readyRead, this,&SerialCOM::SerialDataReady);
}

void SerialCOM::SerialDataReady()
{

}

void SerialCOM::COMChanged(QSerialPortInfo Info, Ui::MainWindow *ui)
{

}





