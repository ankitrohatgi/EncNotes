#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include<string>

class FileManager
{
private:
    std::string fileNameWithPath;
    unsigned char* contents;
    int contentLength;

public:
    FileManager();
    unsigned char* getContent(int *len);
    void setContent(unsigned char* content, int len);
    bool openFile(std::string fileName);
    bool save();
    bool saveas(std::string newFilename);
    void close();
    ~FileManager();

    bool isModified;
};

#endif // FILEMANAGER_H
