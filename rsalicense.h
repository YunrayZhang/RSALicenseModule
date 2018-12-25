#ifndef RSALICENSELIB_LIBRARY_H
#define RSALICENSELIB_LIBRARY_H

#include "biginteger.h"

class RsaAlgrithm
{
private:
    RsaAlgrithm();
    ~RsaAlgrithm();
public:
    //note E is always 0x10001;
    static std::vector<unsigned char> encrypt(const unsigned char *msg, const int msgLen, const BigInteger &N,
                                              const BigInteger &E);
    static std::vector<unsigned char> decrypt(const unsigned char *cipher, const int cipherLen, const BigInteger &N,
                                              const BigInteger &D);

};


#endif