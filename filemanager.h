
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "QString"
#include "QVector"
#include "QWidget"



struct CodeSnippet{
    QString Includes;
    QString Variables;
    QString Setup;
    QString Loop;
};

inline QVector<CodeSnippet> CodeSnippets;


class FileManager
{
public:
    FileManager();
    FileManager(class MainWindow* mw = nullptr){this->mw = mw;};

private:

    class MainWindow* mw;

    bool CheckIfAlreadyContainsSnippet(CodeSnippet snippet);
    void SetIndexForVariables(QString& FileContent, int index);
    void WriteToInoFile(const QString& Content);

public:


    static CodeSnippet GetCodeSnippetFromFile(QString FileLocation);
    CodeSnippet GetAndReplaceCodeSnippetFromSensor(class Sensor sensor);
    void AddCodeSnippetToIno(CodeSnippet Snippet);
    static void ReplacePinNames(QString &Content, QVector<struct Pin> Pins);
    static void RemoveCodeSnippet(CodeSnippet Snippet);
    static void ReplaceSettings(QString &Content, QVector<struct MeasureSetting> Settings);
    static QString GetFileContent(QString path);


    void SetupFileForSensor(Sensor sensor);


public slots:
    void SettingChanged(const QString& variableName, const QString& Value);
};

#endif // FILEMANAGER_H
