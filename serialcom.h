#ifndef SERIALCOM_H
#define SERIALCOM_H

#include "QString"
#include "mainwindow.h"

class SerialCOM
{
public:
    SerialCOM();

private:

    QStringList* Ports;
    QString COMPort;

    class QSerialPort *mSerial;

public:

    void SerialDataReady();

    void COMChanged(class QSerialPortInfo Info, Ui::MainWindow* ui);

    //Getter and Setter
};

#endif // SERIALCOM_H
