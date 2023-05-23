#include "serialcom.h"
#include "qserialportinfo.h"

SerialCOM::SerialCOM()
{



    auto SerialPorts = QSerialPortInfo::availablePorts();
    for (QSerialPortInfo Port : SerialPorts){
        Ports->append(Port.portName());
    }



}

void SerialCOM::COMChanged(QSerialPortInfo Info, Ui::MainWindow *ui)
{

}





