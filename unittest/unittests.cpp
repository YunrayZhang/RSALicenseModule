//
// Created by zhangyl-j on 2019/3/19.
//

#include "gtest/gtest.h"
#include "src/Base64.h"
#include "src/rsalicense.h"
std::string N = "D083F8CC87B311A2C93A68598F4302AAAFC8972D8E46DF2D63445F404781F8A24A862CB36B50860B8E7FDD4E0F6EFFF2D2779397ED2BC65DE2841CD27EF2B031C713B9D9C9F5E2479FD15716934E08616699F025DD0C86399FF6814B7470B6CDF7EA5A15F369355E539541918B9D9E03DC2A8E283B7FD05B676BA4313452B109";
std::string D = "15C8136F5A258C8C12B5353D55C7CC39844F51EB825748ECF6D7A7939164B4524FB2A06CC5A30DBD9B4F2411096FB0F0EEA76B158DC2EADFD7CFB12B13F3CA0FD8B6A880CDB5C4E6BC4D878E10C82786151B1EE862675318026117DDA699F973B70AB7E8659EDC4BDCFF72EDF66A273408C574F0EA80E0A245513943F55ADEF9";
std::string E = "10001";
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
    EXPECT_STREQ((char*)result.data(), "ABC");
}

TEST(RSALicenseLib, test_RSAEncode)
{
    std::string input = "hello world";
    std::string expect = "MfkJZM3Fouc3X0EDpGZ6f3TfPkshW++4/MSGatlpMiXhjTtP4rbDtgXYMoGi1dQHORxbmn/33/QzpWtU3Iu3sm0x/udsbRm8BccZgd+sONHjwA5kvLoheHeLgmuABTqlVdYa3wgtnycgOZgCiUScV8sOTb+VRcsWuBlBDwkTBbA=";
    std::string result = RsaAlgrithm::encrypt_base64ed((const unsigned char*)input.c_str(), input.length(), N, D);

    EXPECT_EQ(expect, result);

}
