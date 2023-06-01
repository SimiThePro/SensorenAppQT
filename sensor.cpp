#include "sensor.h"
#include "filemanager.h"


Sensor::Sensor()
{
    Snippet = FileManager::GetCodeSnippetFromFile(GetCodeSnippetFileLocation());
}

Sensor::Sensor(QString IconFilePath,QString Type, QString Description, QVector<struct Pin> Pins,QVector<ValueMeasure> Measures)
{
    this->IconFilePath = IconFilePath;
    this->Type = Type;
    this->Description = Description;
    this->Pins = Pins;
    this->Measures = Measures;
    this->Snippet = FileManager::GetCodeSnippetFromFile(GetCodeSnippetFileLocation());
}

QString Sensor::GetCodeSnippetFileLocation() const
{
    QString TypeWithoutSpace = this->Type;
    TypeWithoutSpace.remove(' ');


    return static_cast<QString>(PROJECT_PATH) + "Files/" + TypeWithoutSpace + ".txt";
}



void InitializeSensoren()
{

}
