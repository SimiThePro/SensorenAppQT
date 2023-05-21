
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QProcess"
#include "QtSerialPort/QSerialPort"
#include "QtSerialPort/QSerialPortInfo"
#include "QDebug"
#include "QDir"
#include "QElapsedTimer"
#include "QEventLoop"
#include "filemanager.h"
#include "addsensor.h"

#define _STR(x) #x
#define STR(x) _STR(x)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    auto SerialPorts = QSerialPortInfo::availablePorts();
    for (QSerialPortInfo Port : SerialPorts){
        Ports.append(Port.portName() + " " + Port.description());
    }
    ui->COMSelect->addItems(Ports);

    CLI = new QProcess;
    Compile = new QProcess;
    Upload = new QProcess;
    CLI_Location = "C:\\Users\\simim\\Documents\\Arduino-CLI\\arduino-cli.exe";

    Ino_Location = static_cast<QString>(PROJECT_PATH) + "Sketch";

    InitializeArduino();


    fm = new FileManager;
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::Compiling()
{
    QElapsedTimer timer;
    arguments.clear();
    arguments << "compile" << "--fqbn" << "arduino:avr:uno" << Ino_Location << "-v";
    timer.start();
    Compile->startDetached(CLI_Location,arguments);
    Compile->close();

}

void MainWindow::Uploading()
{

    qWarning() << "Uploading";
    arguments.clear();

    arguments << "compile" << "--upload" << "--port" << "COM4" << "--fqbn" << "arduino:avr:uno" << Ino_Location;

    Upload->startDetached(CLI_Location,arguments);
}


void MainWindow::InitializeArduino()
{
    QString Output;

    /*
    arguments.clear();
    arguments << "config" << "init" << "--overwrite";
    CLI->startDetached(CLI_Location,arguments);
    CLI->close();
    arguments.clear();
    arguments << "sketch" << "new" << Ino_Location;
    CLI->startDetached(CLI_Location,arguments);
    CLI->close();

    arguments.clear();
    arguments << "core" << "update-index";
    CLI->startDetached(CLI_Location,arguments);
    CLI->close();


    arguments.clear();
    arguments << "board" << "list";
    CLI->startDetached(CLI_Location,arguments);
    while (CLI->canReadLine()){
        Output += CLI->readLine();
    }

    CLI->close();
    */
}


void MainWindow::on_pushButton_2_clicked()
{

    //CodeSnippet snippet = fm->GetCodeSnippetFromFile(static_cast<QString>(PROJECT_PATH) + "Files/LEDBUILTIN.txt");
    //fm->AddCodeSnippetToIno(snippet);
    //Uploading();
    //fm->RemoveCodeSnippet(snippet);


    AddSensor* sensor = new AddSensor;
    sensor->show();
}

