#include "rsalicense.h"
#include "src/Base64.h"

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

std::string
RsaAlgrithm::encrypt_base64ed(const unsigned char *msg, const int msgLen, const BigInteger &N, const BigInteger &E) {
    std::vector<unsigned char> cipher_vec = encrypt(msg, msgLen, N, E);
    return Base64::Encode(cipher_vec);
}


std::vector<unsigned char> RsaAlgrithm::decrypt_base64ed(const std::string & input,
                                                         const BigInteger &N, const BigInteger &D) {
    std::vector<unsigned char> cipher_byte_stream = Base64::Decode(input);
    return decrypt(cipher_byte_stream.data(), cipher_byte_stream.size(), N , D);
}