#ifndef SERIAL_H
#define SERIAL_H

#include "mainwindow.h"

class Serial : public QObject
{
    Q_OBJECT
public:
    explicit Serial(QObject *parent = nullptr);

private:


    class QSerialPort *mSerial;

public:
    void OpenSerialPort();


private:

    QProcess* CLI;
    QProcess* Compile;
    QProcess* Upload;
    QString CLI_Location;
    QStringList arguments;
    QStringList Ports;
    QString Ino_Location;

    QString ArduinoPort;

    QString UploadOutput;

    QString Message;
    QString serialBuffer;

    bool bShouldRead;



private slots:
    void ReadyRead();
    void ReadProcess();
signals:

    void MessageReceived(QString Message);
public:

    void Compiling();
    void Uploading();

};

#endif // SERIAL_H
