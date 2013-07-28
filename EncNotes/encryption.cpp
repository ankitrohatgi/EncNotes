#include "encryption.h"
#include <openssl/evp.h>
#include <string>
#include <openssl/evp.h>

Encryption::Encryption()
{
    currentPassword = "";
}

void Encryption::setPassword(std::string passwd)
{
    currentPassword = passwd;
}

unsigned char* Encryption::encryptString(unsigned char* plainText, int *len)
{
    EVP_CIPHER_CTX ctx;
    EVP_CIPHER_CTX_init(&ctx);

    const EVP_CIPHER *cipher = EVP_aes_128_cbc();

    unsigned char key1[16];

    generateKey(key1);

    EVP_EncryptInit(&ctx, cipher, key1, key1);

    unsigned char *out = new unsigned char[*len+16];
    int outlen, flen;

    EVP_EncryptUpdate(&ctx, out, &outlen, plainText, *len);

    EVP_EncryptFinal(&ctx, out + outlen, &flen);

    EVP_CIPHER_CTX_cleanup(&ctx);

    *len = outlen + flen;

    return out;
}

unsigned char* Encryption::decryptString(unsigned char* decryptText, int *len)
{
    EVP_CIPHER_CTX ctx;
    EVP_CIPHER_CTX_init(&ctx);

    const EVP_CIPHER *cipher = EVP_aes_128_cbc();
    unsigned char key1[16];

    generateKey(key1);

    EVP_DecryptInit(&ctx, cipher, key1, key1);

    unsigned char *out = new unsigned char[*len+16];
    int outlen, flen;

    EVP_DecryptUpdate(&ctx, out, &outlen, decryptText, *len);

    EVP_DecryptFinal(&ctx, out + outlen, &flen);

    EVP_CIPHER_CTX_cleanup(&ctx);

    *len = outlen + flen;

    return out;
}

void Encryption::generateKey(unsigned char *key)
{
    const unsigned char salt[] = "ThisIsSomeRandomSalt";
    const int saltlen = 20;
    int iter = 10000;
    int keylen = 16; // For 128 bit encryption

    PKCS5_PBKDF2_HMAC_SHA1(static_cast<const char*>(currentPassword.c_str()), currentPassword.length(), salt, saltlen, iter, keylen, key);
}
