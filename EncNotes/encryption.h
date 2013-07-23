#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

class Encryption
{
public:
    Encryption();
    unsigned char* encryptString(unsigned char* passwd, unsigned char* plainText, int *len);
    unsigned char* decryptString(unsigned char* passwd, unsigned char* decryptText, int *len);
private:
    void generateKey(unsigned char* passwd, int passlen, unsigned char *key);
};

#endif // ENCRYPTION_H
