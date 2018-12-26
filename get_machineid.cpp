#include "getmachineid_internal.h"
#include <ctype.h>
#include <sstream>

u16 mask[5] = { 0x4e25, 0xf4a1, 0x5437, 0xab41, 0x0000 };

static void smear( u16* id )
{
    for ( u32 i = 0; i < 5; i++ )
        for ( u32 j = i; j < 5; j++ )
            if ( i != j )
                id[i] ^= id[j];

    for ( u32 i = 0; i < 5; i++ )
        id[i] ^= mask[i];
}

static void unsmear( u16* id )
{
    for ( u32 i = 0; i < 5; i++ )
        id[i] ^= mask[i];

    for ( u32 i = 0; i < 5; i++ )
        for ( u32 j = 0; j < i; j++ )
            if ( i != j )
                id[4-i] ^= id[4-j];
}

static u16* computeSystemUniqueId()
{
    static u16 id[5];
    static bool computed = false;

    if ( computed ) return id;

    // produce a number that uniquely identifies this system.
    id[0] = getCpuHash();
    id[1] = getVolumeHash();
    getMacHash( id[2], id[3] );

    // fifth block is some checkdigits
    id[4] = 0;
    for ( u32 i = 0; i < 4; i++ )
        id[4] += id[i];

    smear( id );

    computed = true;
    return id;
}

const std::string  getSystemUniqueId()
{
    // get the name of the computer
   std::stringstream buf;
    buf << getMachineName();

    u16* id = computeSystemUniqueId();
    for ( u32 i = 0; i < 5; i++ )
    {
        char num[16];
        snprintf( num, 16, "%x", id[i] );
        buf << "-";
        switch( strlen( num ))
        {
            case 1: buf << "000"; break;
            case 2: buf << "00";  break;
            case 3: buf << "0";   break;
        }
        buf << num;
    }

    const char* p = buf.str().data();
    std::stringstream upperString("");
    while ( *p ) { upperString<<toupper( *p ); p++; }

    return upperString.str();
}