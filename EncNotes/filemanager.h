#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include<string>

class FileManager
{
private:
    std::string fileNameWithPath;
    std::string contents;

public:
    FileManager();
    std::string getContent();
    void setContent(std::string content);
    bool openFile(std::string fileName);
    bool save();
    bool saveas(std::string newFilename);
    void close();
    ~FileManager();

    bool isModified;
};

#endif // FILEMANAGER_H
