#include "rsalicense.h"

#include <iostream>


std::vector<unsigned char> RsaAlgrithm::encrypt(const unsigned char *msg, const int msgLen, const BigInteger &N,
                                                const BigInteger &E) {
    BigInteger plainText(msg, msgLen);
    BigInteger cipher = plainText.modPow(E, N);

    return cipher.toBinaryStream();
}

std::vector<unsigned char> RsaAlgrithm::decrypt(const unsigned char *cipher, const int cipherLen, const BigInteger &N,
                                                const BigInteger &D) {
    BigInteger cipherText(cipher, cipherLen);
    BigInteger plainText = cipherText.modPow(D, N);
    return plainText.toBinaryStream();
}


