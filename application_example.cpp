#include <string>
#include <iostream>
#include <unistd.h>
#include "rsalicense.h"
std::string N = "D083F8CC87B311A2C93A68598F4302AAAFC8972D8E46DF2D63445F404781F8A24A862CB36B50860B8E7FDD4E0F6EFFF2D2779397ED2BC65DE2841CD27EF2B031C713B9D9C9F5E2479FD15716934E08616699F025DD0C86399FF6814B7470B6CDF7EA5A15F369355E539541918B9D9E03DC2A8E283B7FD05B676BA4313452B109";
std::string E = "10001";
void usage()
{
    std::cout<<"RSADecoder [encryped license file path]"<<std::endl;
}

int main (int argc, char *argv[]) {
    if(argc != 2 )
    {
        usage();
        return -1;
    }
    if( access(argv[1], F_OK))
    {
        std::cerr<<" license file is not exist"<<std::endl;
        return -1;
    }

    FILE * fp = fopen(argv[1], "rb");
    if( fp == nullptr)
    {
        std::cerr<<" open license file failed with errno "<<errno<<std::endl;
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    unsigned char * content = new unsigned char[size];
    long byteRead = fread(content, 1, size, fp);
    if( byteRead != size)
    {
        std::cerr<<"read from license file failed, file size "<<size<<" but actually read "<<byteRead<<" bytes, errno is "<<errno<<std::endl;
        return -1;
    }
    fclose(fp);

    //call encrypt function here
    std::vector<unsigned char> cipher = RsaAlgrithm::decrypt(content, size, N, E);
    FILE * licFile = fopen("ok.txt", "wb+");
    if( licFile == nullptr)
    {
        std::cerr<<" create encrypted license file failed with errno "<<errno<<std::endl;
        return -1;
    }

    size_t bytesWrite = fwrite(cipher.data(), 1, cipher.size(), licFile);
    if( bytesWrite != cipher.size())
    {
        std::cerr<<"write encrypted license content failed!"<<std::endl;
        return -1;
    }
    else
    {
        std::cout<<"Generate license succeed!"<<std::endl;
    }
    delete [] content;
    return 0;
}
