
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QProcess"
#include "sensor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void AddSensorToGrid(class Sensor);


private slots:


    void Uploading();
    void on_pushButton_2_clicked();

    void MessageReceived(QString Message);

    void on_CompileButton_clicked();

    void handleTextChanged(const QString& newText);

private:
    Ui::MainWindow *ui;

    void InitializeArduino();

    void Compiling();

    QProcess* CLI;
    QProcess* Compile;
    QProcess* Upload;
    QString CLI_Location;
    QStringList arguments;

    QStringList Ports;

    QString Ino_Location;

    class Serial* serial;
    class FileManager* fm;

    bool bIsCodeUpToDate;

public:

    void NeedToCompile(bool need);
};

inline QVector<class Sensor> VerfuegbareSensoren;
inline QVector<class Sensor> CurrentSensors;
inline QVector<int> UsedDigitalPins{};
inline QVector<int> UsedAnalogPins{};
inline QVector<QLabel*> ValueLables{};

#endif // MAINWINDOW_H
