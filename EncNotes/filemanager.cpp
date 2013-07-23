#include "filemanager.h"
#include <fstream>
#include <iostream>
FileManager::FileManager()
{

}

bool FileManager::openFile(std::string fileName)
{
    fileNameWithPath = fileName;
    std::ifstream fhandle(fileName.c_str(), std::ios::in|std::ios::binary);
    if(fhandle)
    {
        fhandle.seekg(0, std::ios::end);
        contents.resize(fhandle.tellg());
        fhandle.seekg(0, std::ios::beg);
        fhandle.read(&contents[0], contents.size());
        fhandle.close();
        return true;
    }
    return false;
}

std::string FileManager::getContent()
{
    return contents;
}

void FileManager::setContent(std::string content)
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

void FileManager::close()
{

}

FileManager::~FileManager()
{
    this->close();
}
