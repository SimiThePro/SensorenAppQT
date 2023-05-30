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

    QString Message;
    QString serialBuffer;
private slots:
    void ReadyRead();

signals:

    void MessageReceived(QString Message);

};

#endif // SERIAL_H
