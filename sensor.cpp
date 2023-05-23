#include "sensor.h"
#include "filemanager.h"

FileManager fm;

Sensor::Sensor()
{

}

Sensor::Sensor(QString IconFilePath,QString Type, QString Benennung, QVector<struct Pin> Pins, CodeSnippet Snippet)
{
    this->IconFilePath = IconFilePath;
    this->Type = Type;
    this->Benennung = Benennung;
    this->Pins = Pins;
    this->Snippet = Snippet;
}



void InitializeSensoren()
{

}
