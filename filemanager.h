
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "QString"
#include "QVector"




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

private:


    bool CheckIfAlreadyContainsSnippet(CodeSnippet snippet);
    void SetIndexForVariables(QString& FileContent, int index);

public:


    static CodeSnippet GetCodeSnippetFromFile(QString FileLocation);
    CodeSnippet GetAndReplaceCodeSnippetFromSensor(class Sensor sensor);
    void AddCodeSnippetToIno(CodeSnippet Snippet);
    static void ReplacePinNames(QString &Content, QVector<struct Pin> Pins);
    static void RemoveCodeSnippet(CodeSnippet Snippet);
    static QString GetFileContent(QString path);

    void SetupFileForSensor(Sensor sensor);
};

#endif // FILEMANAGER_H
