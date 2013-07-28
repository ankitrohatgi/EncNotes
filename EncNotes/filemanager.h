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

    bool hasFileName();
    void setFileName(std::string filename);

    unsigned char* getContent(int *len);
    void setContent(unsigned char* content, int len);
    bool open();
    bool save();
    bool saveAs(std::string newFilename);
    void close();

    ~FileManager();

    bool isModified;
};

#endif // FILEMANAGER_H
