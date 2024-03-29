
#ifndef SENSOR_H
#define SENSOR_H

#include "QString"
#include "QVector"
#include "filemanager.h"
#include "ui_Sensor.h"

struct Pin{
    int PinNummer;
    QString Description;
    bool isAnalogPin = false;
};

struct ValueMeasure{
    QString Description;
    QString Value = 0;
};



struct MeasureSetting{
    QString Description;
    QVariant variant;
    QString VariableName;
};

class Sensor
{
public:
    Sensor();
    Sensor(QString IconFilePath,
           QString Type,
           QString Description,
           QVector<struct Pin> Pins,
           QVector<ValueMeasure> Measures,
           QVector<MeasureSetting> MeasureSettings = QVector<MeasureSetting>{});
private:



    QString IconFilePath;
    QString Type;
    QString Description;
    QVector<Pin> Pins;
    CodeSnippet Snippet;
    QVector<ValueMeasure> Measures;
    QVector<MeasureSetting> MeasureSettings;
    Ui::Sensor* Ui;

public:
    inline QString GetArt() const {return Type;}
    QString GetIconFilePath() const {return IconFilePath;}
    QVector<Pin> GetPins() const {return Pins;}
    QString GetDescription() const {return Description;}
    QVector<ValueMeasure> GetMeasures() const {return Measures;}
    Ui::Sensor* GetUi() const {return Ui;}
    QString GetCodeSnippetFileLocation() const;
    QVector<MeasureSetting> GetMeasureSettings() const {return MeasureSettings;};

    //Setter
    void SetIconFilePath(QString IconFilePath) {this->IconFilePath = IconFilePath;}
    void SetType(QString Type) {this->Type = Type;}
    void SetDescription(QString Description) {this->Description = Description;}
    void SetPins(QVector<Pin> Pins) {this->Pins = Pins;}
    void SetSnippet(CodeSnippet snippet){this->Snippet = snippet;}
    void SetUi(Ui::Sensor* Ui){this->Ui = Ui;}
    void SetMeasureSettings(QVector<MeasureSetting> MeasureSettings) {this->MeasureSettings = MeasureSettings;}



public slots:
    void SettingValueChanged(const QString& value);
};




void InitializeSensoren();


#endif // SENSOR_H
