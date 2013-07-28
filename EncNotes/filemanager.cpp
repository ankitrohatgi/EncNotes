#include "filemanager.h"
#include <fstream>
#include <iostream>
FileManager::FileManager()
{
    contents = NULL;
}

bool FileManager::openFile(std::string fileName)
{
    fileNameWithPath = fileName;
    std::ifstream fhandle(fileName.c_str(), std::ios::in|std::ios::binary);
    if(fhandle)
    {
        fhandle.seekg(0, std::ios::end);
        contentLength = fhandle.tellg();
        fhandle.seekg(0, std::ios::beg);
        contents = new unsigned char[contentLength];
        fhandle.read(reinterpret_cast<char *>(contents), contentLength);
        fhandle.close();
        std::cout << contents << contentLength << std::endl;
        return true;
    }
    return false;
}

unsigned char* FileManager::getContent(int *len)
{
    *len = contentLength;
    return contents;
}

void FileManager::setContent(unsigned char* content, int len)
{

    contents = content;
}

bool FileManager::save()
{
    return saveas(fileNameWithPath);
}

bool FileManager::saveas(std::string newFilename)
{
    fileNameWithPath = newFilename;
    std::ofstream fhandle(fileNameWithPath.c_str(), std::ios::out|std::ios::binary);
    if(fhandle)
    {
        fhandle << contents;
        fhandle.close();
        return true;
    }
    return false;
}

FileManager::~FileManager()
{
    if(contents!=NULL)
    {
        delete[] contents;
        contents = NULL;
    }
}
