
#include "filemanager.h"
#include "mainwindow.h"
#include "qlineedit.h"
#include "qspinbox.h"
#include "sensor.h"
#include "QFile"
#include "QDebug"


FileManager::FileManager()
{

}

bool FileManager::CheckIfAlreadyContainsSnippet(CodeSnippet snippet)
{
    QString FileContent = GetFileContent(static_cast<QString>(PROJECT_PATH) + "Sketch/Sketch.ino");

    if (FileContent.contains(snippet.Variables) || FileContent.contains(snippet.Setup) || FileContent.contains(snippet.Loop)){
        return false;
    }
}

void FileManager::SetIndexForVariables(QString &Content, int index)
{
    if (Content.contains("_index")){

        if (Content.contains("_index:")){
            while (Content.contains("_index:")){
                Content.replace("_index:",QString::number(index)+ ":");
            }
        }
        if (Content.contains("_index")){
            while (Content.contains("_index")){
                Content.replace("_index","_" + QString::number(index));
            }
        }

    }
}

void FileManager::WriteToInoFile(const QString &Content)
{
    QFile file(static_cast<QString>(PROJECT_PATH)  + "Sketch/Sketch.ino");

    if (!file.open(QIODevice::WriteOnly)){
        qCritical() << "Could not Open File";
        qCritical() << file.errorString(); //pushes data to the disk
        return;
    }

    QTextStream InoStream(&file);

    InoStream << Content;

    file.close();
}

QString FileManager::GetFileContent(QString path)
{
    QFile file(path);
    QString FileContent = "";
    if (!file.exists()){
        qCritical() << "File not found";
        return QString{};
    }

    if (!file.open(QIODevice::ReadOnly)){
        qCritical() << "Could not Open File";
        qCritical() << file.errorString(); //pushes data to the disk
        return QString{};
    }

    QTextStream stream(&file);
    //QString data = file.readAll();
    while (!stream.atEnd()){
        QString line = stream.readLine();
        FileContent += line + '\n';
    }
    file.close();

    return FileContent;


}

void FileManager::SetupFileForSensor(Sensor sensor)
{
    CodeSnippet snippet = GetAndReplaceCodeSnippetFromSensor(sensor);
    AddCodeSnippetToIno(snippet);
}

void FileManager::SettingChanged(const QString &variableName, const QString &Value)
{
    QString FileContent = GetFileContent(static_cast<QString>(PROJECT_PATH) + "Sketch/Sketch.ino");



    if (FileContent.contains(variableName + " =")){

        QString variable = FileContent.sliced(FileContent.indexOf(variableName + " ="),FileContent.indexOf(';',FileContent.indexOf(variableName + " =")) - FileContent.indexOf(variableName + " ="));

        bool bIsString = variable.contains("\"");

        QString fixedValue;

        QString newVariable;

        if (!bIsString){
            for (QChar c : Value){

                if (c == ',') c = '.';
                else if (c.isLetter()) continue;
                else if (c.isSpace()) continue;
                fixedValue.append(c);
            }

            newVariable = variableName + " = " + fixedValue;


        }else {
            newVariable = variableName + " = " +  "\"" + Value + "\"";
        }


        FileContent.replace(variable,newVariable);

        for (CodeSnippet &snippets : CodeSnippets){
            snippets.Variables.replace(variable,newVariable);
            snippets.Setup.replace(variable,newVariable);
            snippets.Loop.replace(variable,newVariable);
        }

        if (variable.sliced(variable.indexOf('=')+2).contains(QRegularExpression("\\d*"))){
            qInfo() << "Number";
        }if(variable.sliced(variable.indexOf('=')+2).contains(QRegularExpression("\\w*"))){
            qInfo() << "Letters";
        }
    }

    mw->NeedToCompile(true);

    WriteToInoFile(FileContent);
}

CodeSnippet FileManager::GetCodeSnippetFromFile(QString FileLocation)
{
    QString FileContent = GetFileContent(FileLocation);

    if (FileContent == "") return CodeSnippet{};

    QString Includes;
    QString Variables;
    QString Setup;
    QString Loop;

    Includes = FileContent.sliced(0, FileContent.indexOf("~Variables")-10);
    Variables = FileContent.sliced(FileContent.indexOf("~Variables")+10,FileContent.indexOf("~Setup")-FileContent.indexOf("~Variables")-11);
    Setup = FileContent.sliced(FileContent.indexOf("~Setup")+7,FileContent.indexOf("~Loop")-FileContent.indexOf("~Setup")-7);
    Loop =  FileContent.sliced(FileContent.indexOf("~Loop")+6);

    /*
    qInfo() << Includes;
    qInfo() << Variables;
    qInfo() << Setup;
    qInfo() << Loop;
    */

    /*
    QFile Testfile("C:\\Users\\simim\\Documents\\QT\\Personal\\SensorenApp\\Files\\Test.txt");
    if (!Testfile.open(QIODevice::WriteOnly)){
        qCritical() << "Could not Open File";
        qCritical() << file.errorString(); //pushes data to the disk
        return;
    }

    QTextStream Teststream(&Testfile);

    Teststream << Includes << Variables << Setup << Loop;

    Testfile.close();
    */




    CodeSnippet snippet = {Includes,Variables,Setup,Loop};

    return snippet;

}

CodeSnippet FileManager::GetAndReplaceCodeSnippetFromSensor(Sensor sensor)
{
    QString FileContent = GetFileContent(sensor.GetCodeSnippetFileLocation());

    ReplacePinNames(FileContent,sensor.GetPins());
    SetIndexForVariables(FileContent,CurrentSensors.size());

    QString Includes;
    QString Variables;
    QString Setup;
    QString Loop;

    Includes = FileContent.sliced(10, FileContent.indexOf("~Variables")-10);
    Variables = FileContent.sliced(FileContent.indexOf("~Variables")+11,FileContent.indexOf("~Setup")-FileContent.indexOf("~Variables")-11);
    Setup = FileContent.sliced(FileContent.indexOf("~Setup")+7,FileContent.indexOf("~Loop")-FileContent.indexOf("~Setup")-7);
    Loop =  FileContent.sliced(FileContent.indexOf("~Loop")+6);

    qInfo() << Includes;
    qInfo() << Variables;
    qInfo() << Setup;
    qInfo() << Loop;


    CodeSnippet snippet = {Includes,Variables,Setup,Loop};

    return snippet;

}


void FileManager::AddCodeSnippetToIno(CodeSnippet Snippet)
{

    //if (CheckIfAlreadyContainsSnippet(Snippet)) return;

    CodeSnippets.push_back(Snippet);

    QString FileContent = GetFileContent(static_cast<QString>(PROJECT_PATH) + "Sketch/Sketch.ino");

    FileContent.insert(FileContent.lastIndexOf("#pragma endregion Includes"),Snippet.Includes);
    FileContent.insert(FileContent.lastIndexOf("#pragma endregion Variables"),Snippet.Variables);
    FileContent.insert(FileContent.lastIndexOf("#pragma endregion Setup"),Snippet.Setup);
    FileContent.insert(FileContent.lastIndexOf("#pragma endregion Loop"),Snippet.Loop);


    QFile file(static_cast<QString>(PROJECT_PATH)  + "Sketch/Sketch.ino");

    if (!file.open(QIODevice::WriteOnly)){
        qCritical() << "Could not Open File";
        qCritical() << file.errorString(); //pushes data to the disk
        return;
    }

    QTextStream InoStream(&file);

    InoStream << FileContent;

    file.close();

}

void FileManager::ReplacePinNames(QString &Content, QVector<Pin> Pins)
{
    if (Content.contains("_analogPin") || Content.contains("_digitalPin")){
        if (Content.contains("_digitalPin")){
            for (int i = 0; Content.contains("_digitalPin"); i++){
                while (Content.contains("_digitalPin" + QString::number(i))){
                    Content.replace("_digitalPin" + QString::number(i),QString::number(Pins.at(i).PinNummer));
                }
            }
        }
        if (Content.contains("_analogPin")){
            for (int i = 0; Content.contains("_analogPin"); i++){
                while (Content.contains("_analogPin" + QString::number(i))){
                    Content.replace("_analogPin" + QString::number(i), "A" + QString::number(Pins.at(i).PinNummer));
                }
            }
        }
    }

}

void FileManager::RemoveCodeSnippet(CodeSnippet Snippet)
{

    QString FileContent = GetFileContent(static_cast<QString>(PROJECT_PATH)  + "Sketch/Sketch.ino");

    if (Snippet.Includes != "" || Snippet.Includes != "\n")
    FileContent.remove(Snippet.Includes);
    if (Snippet.Variables != "" || Snippet.Variables != "\n")
    FileContent.remove(Snippet.Variables);
    if (Snippet.Setup != "" || Snippet.Setup != "\n")
    FileContent.remove(Snippet.Setup);
    if (Snippet.Loop != "" || Snippet.Loop != "\n")
    FileContent.remove(Snippet.Loop);

    QFile file(static_cast<QString>(PROJECT_PATH)  + "Sketch/Sketch.ino");

    if (!file.open(QIODevice::WriteOnly)){
    qCritical() << "Could not Open File";
    qCritical() << file.errorString(); //pushes data to the disk
    return;
    }

    QTextStream InoStream(&file);

    InoStream << FileContent;

    file.close();


}



