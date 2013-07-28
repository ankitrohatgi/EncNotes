#include "filemanager.h"
#include <fstream>
#include <iostream>
FileManager::FileManager()
{
    contents = NULL;
    fileNameWithPath = "";
}

bool FileManager::hasFileName()
{
    return fileNameWithPath.length() > 0;
}

void FileManager::setFileName(std::string filename)
{
    fileNameWithPath = filename;
}

bool FileManager::open()
{
    if(!hasFileName()) return false;

    std::ifstream fhandle(fileNameWithPath.c_str(), std::ios::in|std::ios::binary);
    if(!fhandle) return false;

    fhandle.seekg(0, std::ios::end);
    contentLength = fhandle.tellg();
    fhandle.seekg(0, std::ios::beg);
    contents = new unsigned char[contentLength];
    fhandle.read(reinterpret_cast<char *>(contents), contentLength);
    fhandle.close();
    return true;
}

unsigned char* FileManager::getContent(int *len)
{
    *len = contentLength;
    return contents;
}

void FileManager::setContent(unsigned char* content, int len)
{
    contentLength = len;
    contents = content;
}

bool FileManager::save()
{
    if(!hasFileName()) return false;

    return saveAs(fileNameWithPath);
}

bool FileManager::saveAs(std::string newFilename)
{
    fileNameWithPath = newFilename;
    std::ofstream fhandle(fileNameWithPath.c_str(), std::ios::out|std::ios::binary);
    if(!fhandle) return false;

    //fhandle.seekg(0, std::ios::beg);
    fhandle.write(reinterpret_cast<char *>(contents), contentLength);
    fhandle.close();
    return true;
}

FileManager::~FileManager()
{
    if(contents!=NULL)
    {
        delete[] contents;
    }
}
