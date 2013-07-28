#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

class Encryption
{
    std::string currentPassword;
public:
    Encryption();
    void setPassword(std::string passwd);
    unsigned char* encryptString(unsigned char* plainText, int *len);
    unsigned char* decryptString(unsigned char* decryptText, int *len);
private:
    void generateKey(unsigned char *key);
};

#endif // ENCRYPTION_H
