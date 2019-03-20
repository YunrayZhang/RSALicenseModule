#include "rsalicense.h"
#include "src/Base64.h"

std::string RsaAlgrithm::encrypt(const unsigned char *msg, int msgLen, const BigInteger &N,
                                 const BigInteger &E) {
    BigInteger plainText(msg, msgLen);
    BigInteger cipher = plainText.modPow(E, N);
    return cipher.toString();
}

std::vector<unsigned char> RsaAlgrithm::decrypt(const unsigned char *cipher, int cipherLen, const BigInteger &N,
                                                const BigInteger &D) {
    std::string cipher_string = std::string((const char*)cipher, cipherLen);
    BigInteger cipherText(cipher_string);
    BigInteger plainText = cipherText.modPow(D, N);
    return plainText.toBinaryStream();
}

std::string
RsaAlgrithm::encrypt_base64ed(const unsigned char *msg, const int msgLen, const BigInteger &N, const BigInteger &E) {
    std::string cipher_string = encrypt(msg, msgLen, N, E);
    return Base64::Encode(std::vector<unsigned char>(cipher_string.begin(), cipher_string.end()));
}


std::vector<unsigned char> RsaAlgrithm::decrypt_base64ed(const std::string & input,
                                                         const BigInteger &N, const BigInteger &D) {
    std::vector<unsigned char> cipher_byte_stream = Base64::Decode(input);
    return decrypt(cipher_byte_stream.data(), cipher_byte_stream.size(), N , D);
}
