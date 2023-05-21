
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

inline QVector<CodeSnippet*> CodeSnippets;


class FileManager
{
public:
    FileManager();

private:

    QString GetFileContent(QString path);

public:
    CodeSnippet GetCodeSnippetFromFile(QString FileLocation);
    void AddCodeSnippetToIno(CodeSnippet Snippet);
    void RemoveCodeSnippet(CodeSnippet Snippet);
};

#endif // FILEMANAGER_H
