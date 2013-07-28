#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

class Encryption
{
public:
    Encryption();
    unsigned char* encryptString(std::string passwd, unsigned char* plainText, int *len);
    unsigned char* decryptString(std::string passwd, unsigned char* decryptText, int *len);
private:
    void generateKey(std::string passwd, unsigned char *key);
};

#endif // ENCRYPTION_H
