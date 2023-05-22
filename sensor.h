
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
};

QString ImageFilePath = static_cast<QString>(PROJECT_PATH) + "Images";


inline QVector<Sensor> VerfuegbareSensoren;
void InitializeSensoren();


#endif // SENSOR_H
