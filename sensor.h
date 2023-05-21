
#ifndef SENSOR_H
#define SENSOR_H

#include "QString"
#include "QVector"

struct Pin{
    int Pin;
    QString Description;
};

class Sensor
{
public:
    Sensor();
    Sensor(QString IconFilePath,QString Art, QString Benennung, QVector< struct Pin> Pins);
private:



    QString IconFilePath;
    QString Art;
    QString Benennung;

    QVector<Pin> Pins;

};

QString ImageFilePath = static_cast<QString>(PROJECT_PATH) + "Images";


inline QVector<Sensor> VerfuegbareSensoren;
void InitializeSensoren();


#endif // SENSOR_H
