
#ifndef SENSOR_H
#define SENSOR_H

#include "QString"
#include "QVector"
#include "filemanager.h"

struct Pin{
    int PinNummer;
    QString Description;
};

class Sensor
{
public:
    Sensor();
    Sensor(QString IconFilePath,QString Type, QString Benennung, QVector<struct Pin> Pins,class CodeSnippet Snippet);
private:



    QString IconFilePath;
    QString Type;
    QString Benennung;
    QVector<Pin> Pins;
    CodeSnippet Snippet;


public:
    QString GetArt() const {return Type;}
    QString GetIconFilePath() const {return IconFilePath;}
    QVector<Pin> GetPins() const {return Pins;}
};




void InitializeSensoren();


#endif // SENSOR_H
