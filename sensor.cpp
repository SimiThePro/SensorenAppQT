
#include "sensor.h"

Sensor::Sensor()
{

}

Sensor::Sensor(QString IconFilePath,QString Art, QString Benennung, QVector<struct Pin> Pins)
{
    this->IconFilePath = IconFilePath;
    this->Art = Art;
    this->Benennung = Benennung;
    this->Pins = Pins;
}

