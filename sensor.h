
#ifndef SENSOR_H
#define SENSOR_H

#include "QString"
#include "QVector"
#include "filemanager.h"
#include "ui_Sensor.h"

struct Pin{
    int PinNummer;
    QString Description;
};

struct Messung{
    QString Description;
    QString Value;
};

class Sensor
{
public:
    Sensor();
    Sensor(QString IconFilePath,QString Type, QString Description, QVector<struct Pin> Pins,class CodeSnippet Snippet);
private:



    QString IconFilePath;
    QString Type;
    QString Description;
    QVector<Pin> Pins;
    CodeSnippet Snippet;
    Ui::Sensor* Ui;

public:
    QString GetArt() const {return Type;}
    QString GetIconFilePath() const {return IconFilePath;}
    QVector<Pin> GetPins() const {return Pins;}
    QString GetDescription() const {return Description;}
    Ui::Sensor* GetUi() const {return Ui;}
    //Setter
    void SetIconFilePath(QString IconFilePath) {this->IconFilePath = IconFilePath;}
    void SetType(QString Type) {this->Type = Type;}
    void SetDescription(QString Description) {this->Description = Description;}
    void SetPins(QVector<Pin> Pins) {this->Pins = Pins;}
    void SetSnippet(CodeSnippet snippet){this->Snippet = snippet;}
    void SetUi(Ui::Sensor* Ui){this->Ui = Ui;}
};




void InitializeSensoren();


#endif // SENSOR_H
