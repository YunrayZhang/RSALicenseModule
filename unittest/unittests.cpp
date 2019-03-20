//
// Created by zhangyl-j on 2019/3/19.
//

#include "gtest/gtest.h"
#include "src/Base64.h"
#include "src/rsalicense.h"
static std::string N = "D083F8CC87B311A2C93A68598F4302AAAFC8972D8E46DF2D63445F404781F8A24A862CB36B50860B8E7FDD4E0F6EFFF2D2779397ED2BC65DE2841CD27EF2B031C713B9D9C9F5E2479FD15716934E08616699F025DD0C86399FF6814B7470B6CDF7EA5A15F369355E539541918B9D9E03DC2A8E283B7FD05B676BA4313452B109";
static std::string D = "15C8136F5A258C8C12B5353D55C7CC39844F51EB825748ECF6D7A7939164B4524FB2A06CC5A30DBD9B4F2411096FB0F0EEA76B158DC2EADFD7CFB12B13F3CA0FD8B6A880CDB5C4E6BC4D878E10C82786151B1EE862675318026117DDA699F973B70AB7E8659EDC4BDCFF72EDF66A273408C574F0EA80E0A245513943F55ADEF9";
static std::string E = "10001";
TEST(Base64Test, test_encode_when_input_ABC_encodedto_QUJD)
{
    std::vector<unsigned char> input={'A','B','C'};
    std::string result = Base64::Encode(input);
    EXPECT_STREQ(result.data(), std::string("QUJD").data());
}

TEST(Base64Test, test_decode_when_input_QUJD_decodedto_abc)
{
    std::string input = "QUJD";
    std::vector<unsigned char> result = Base64::Decode(input);
    std::vector<unsigned char> expect = {'A', 'B', 'C'};
    EXPECT_EQ(expect, result);
}

TEST(RSALicenseLib, test_RSAEncode)
{
    std::string input = "hello world";
    std::string expect = "31F90964CDC5A2E7375F4103A4667A7F74DF3E4B215BEFB8FCC4866AD9693225E18D3B4FE2B6C3B605D83281A2D5D407391C5B9A7FF7DFF433A56B54DC8BB7B26D31FEE76C6D19BC05C71981DFAC38D1E3C00E64BCBA2178778B826B80053AA555D61ADF082D9F272039980289449C57CB0E4DBF9545CB16B819410F091305B0";
    std::string result = RsaAlgrithm::encrypt((const unsigned char*)input.c_str(), input.length(), N, D);

    EXPECT_EQ(expect, result);

}

TEST(RSALicenseLib, test_RSADecode)
{
    std::string input = "31F90964CDC5A2E7375F4103A4667A7F74DF3E4B215BEFB8FCC4866AD9693225E18D3B4FE2B6C3B605D83281A2D5D407391C5B9A7FF7DFF433A56B54DC8BB7B26D31FEE76C6D19BC05C71981DFAC38D1E3C00E64BCBA2178778B826B80053AA555D61ADF082D9F272039980289449C57CB0E4DBF9545CB16B819410F091305B0";
    std::string expect = "hello world";
    std::vector<unsigned char > ret = RsaAlgrithm::decrypt((const unsigned char*)input.data(), input.length(), N, E);
    EXPECT_EQ(std::vector<unsigned char>(expect.begin(), expect.end()), ret);
}

TEST(RSALicenseLib, test_RSAEncodeBase64ed)
{
    std::string input = "hello world";
    std::string expect = "MzFGOTA5NjRDREM1QTJFNzM3NUY0MTAzQTQ2NjdBN0Y3NERGM0U0QjIxNUJFRkI4RkNDNDg2NkFEOTY5MzIyNUUxOEQzQjRGRTJCNkMzQjYwNUQ4MzI4MUEyRDVENDA3MzkxQzVCOUE3RkY3REZGNDMzQTU2QjU0REM4QkI3QjI2RDMxRkVFNzZDNkQxOUJDMDVDNzE5ODFERkFDMzhEMUUzQzAwRTY0QkNCQTIxNzg3NzhCODI2QjgwMDUzQUE1NTVENjFBREYwODJEOUYyNzIwMzk5ODAyODk0NDlDNTdDQjBFNERCRjk1NDVDQjE2QjgxOTQxMEYwOTEzMDVCMA==";
    std::string result = RsaAlgrithm::encrypt_base64ed((const unsigned char*)input.c_str(), input.length(), N, D);

    EXPECT_EQ(expect, result);
}

TEST(RSALicenseLib, test_RSADecodeBase64ed)
{
    std::string cipher = "MzFGOTA5NjRDREM1QTJFNzM3NUY0MTAzQTQ2NjdBN0Y3NERGM0U0QjIxNUJFRkI4RkNDNDg2NkFEOTY5MzIyNUUxOEQzQjRGRTJCNkMzQjYwNUQ4MzI4MUEyRDVENDA3MzkxQzVCOUE3RkY3REZGNDMzQTU2QjU0REM4QkI3QjI2RDMxRkVFNzZDNkQxOUJDMDVDNzE5ODFERkFDMzhEMUUzQzAwRTY0QkNCQTIxNzg3NzhCODI2QjgwMDUzQUE1NTVENjFBREYwODJEOUYyNzIwMzk5ODAyODk0NDlDNTdDQjBFNERCRjk1NDVDQjE2QjgxOTQxMEYwOTEzMDVCMA==";
    std::string expect = "hello world";
    std::vector<unsigned char> paintext = RsaAlgrithm::decrypt_base64ed(cipher, N, E);
    std::cout<<paintext.data()<<std::endl;
    EXPECT_EQ(std::vector<unsigned char> (expect.begin(), expect.end()), paintext);
}