#include "getmachineid_internal.h"
#include <string.h>
#include <ctype.h>
#include <sstream>
#include <stdio.h>
#include <algorithm>

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
#if defined(WIN32)
        _snprintf_s( num, 16, "%x", id[i] );        
#else
        snprintf( num, 16, "%x", id[i] );
#endif
        buf << "»";
        switch( strlen( num ))
        {
            case 1: buf << "000"; break;
            case 2: buf << "00";  break;
            case 3: buf << "0";   break;
        }
        buf << num;
    }
    std::string strBuf = buf.str();
    std::transform(strBuf.begin(), strBuf.end(), strBuf.begin(), ::toupper);

    return strBuf;
}

bool validate_machine_fp(std::string testIdString)
{
    // unpack the given string. parse failures return false.
    char * testString = new char[testIdString.size()+1];
    memset(testString, 0, testIdString.size()+1);
    memcpy(testString, testIdString.data(), testIdString.size());
    char* testName = strtok( testString, "»" );
    if ( !testName ) return false;

    u16 testId[5];
    for ( u32 i = 0; i < 5; i++ )
    {
        char* testNum = strtok( NULL, "»" );
        if ( !testNum ) return false;
        testId[i] = (u16)(strtol( testNum, NULL, 16 ));
    }
    unsmear( testId );

    // make sure this id is valid - by looking at the checkdigits
    u16 check = 0;
    for ( u32 i = 0; i < 4; i++ )
        check += testId[i];
    if ( check != testId[4] ) return false;

    // get the current system information
    u16 systemId[5];
    memcpy( systemId, computeSystemUniqueId(), sizeof( systemId ));
    unsmear( systemId );

    // now start scoring the match
    u32 score = 0;

    for ( u32 i = 0; i < 4; i++ )
        if ( testId[i] == systemId[i] )
            score++;

    if ( !strcmp( getMachineName(), testName ))
        score++;

    // if we score 3 points or more then the id matches.
    return ( score >= 3 ) ? true : false;
}