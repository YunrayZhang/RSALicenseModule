#ifndef GET_MACHINEID_H
#define GET_MACHINEID_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
void getMacHash( u16& mac1, u16& mac2 );
u16 getVolumeHash();
u16 getCpuHash();
const char* getMachineName();
#endif