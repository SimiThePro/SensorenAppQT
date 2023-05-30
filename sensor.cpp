#include "sensor.h"
#include "filemanager.h"


Sensor::Sensor()
{

}

Sensor::Sensor(QString IconFilePath,QString Type, QString Description, QVector<struct Pin> Pins, CodeSnippet Snippet)
{
    this->IconFilePath = IconFilePath;
    this->Type = Type;
    this->Description = Description;
    this->Pins = Pins;
    this->Snippet = Snippet;
}



void InitializeSensoren()
{

}
