
#include "sensor.h"
#include "filemanager.h"

FileManager fm;

Sensor::Sensor()
{

}

Sensor::Sensor(QString IconFilePath,QString Art, QString Benennung, QVector<struct Pin> Pins, CodeSnippet Snippet)
{
    this->IconFilePath = IconFilePath;
    this->Art = Art;
    this->Benennung = Benennung;
    this->Pins = Pins;
    this->Snippet = Snippet;
}



void InitializeSensoren()
{

}
