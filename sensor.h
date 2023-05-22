
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
    Sensor(QString IconFilePath,QString Art, QString Benennung, QVector<Pin> Pins,class CodeSnippet Snippet);
private:



    QString IconFilePath;
    QString Art;
    QString Benennung;
    QVector<Pin> Pins;
    CodeSnippet Snippet;


public:
    QString GetArt() const {return Art;}
    QString GetIconFilePath() const {return IconFilePath;}
    QVector<Pin> GetPins() const {return Pins;}
};




void InitializeSensoren();


#endif // SENSOR_H
