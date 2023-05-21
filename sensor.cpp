
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
    QString ProjectPath =  static_cast<QString>(PROJECT_PATH);

    Sensor sensor{ProjectPath + "/Images/Photoresitor.png","Photoresistor","",QVector<Pin>{{1,"OUTPUT"}},fm.GetCodeSnippetFromFile(ProjectPath + "/Files/LEDBUILTIN.txt")};

    QVector<Pin>{{1,"OUTPUT"},{2,"TRIGGER"}};

    VerfuegbareSensoren.push_back(Sensor{
        ProjectPath + "/Images/Photoresitor.png",
        "Photoresistor",
        "",
        QVector<Pin>{{1,"OUTPUT"}},
        fm.GetCodeSnippetFromFile(ProjectPath + "/Files/LEDBUILTIN.txt")});

    VerfuegbareSensoren.push_back(Sensor{
        ProjectPath + "/Images/Ultraschall.jpg",
        "Supersonic",
        "",
        QVector<Pin>{{1,"TRIGGER"},{2,"ECHO"}},
        fm.GetCodeSnippetFromFile(ProjectPath + "/Files/LEDBUILTIN.txt")
    });
}
