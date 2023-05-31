#include "sensor.h"
#include "filemanager.h"


Sensor::Sensor()
{

}

Sensor::Sensor(QString IconFilePath,QString Type, QString Description, QVector<struct Pin> Pins,QVector<ValueMeasure> Measures,CodeSnippet Snippet)
{
    this->IconFilePath = IconFilePath;
    this->Type = Type;
    this->Description = Description;
    this->Pins = Pins;
    this->Measures = Measures;
    this->Snippet = Snippet;
}



void InitializeSensoren()
{

}
