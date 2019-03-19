#ifndef RSALICENSELIB_LIBRARY_H
#define RSALICENSELIB_LIBRARY_H

#include "src/biginteger.h"

class RsaAlgrithm
{
private:
    RsaAlgrithm();
    ~RsaAlgrithm();
public:
    //note E is always 0x10001;
    static std::vector<unsigned char> encrypt(const unsigned char *msg, const int msgLen, const BigInteger &N,
                                              const BigInteger &E);
    //RSA Encode and then use base64 to encode to make the cipher readable
    static std::string encrypt_base64ed(const unsigned char *msg, const int msgLen, const BigInteger &N,
                                              const BigInteger &E);

    //RSA decode
    static std::vector<unsigned char> decrypt(const unsigned char *cipher, const int cipherLen, const BigInteger &N,
                                              const BigInteger &D);

    //RSA decode with base64 decode first and then using RSA to decode as the cipher is base64encoded
    static std::vector<unsigned char> decrypt_base64ed(const std::string & input, const BigInteger& N,
                                              const BigInteger &D);

};


#endif