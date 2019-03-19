#include <windows.h>
#include <intrin.h>
#include <iphlpapi.h>
#include "getmachineid_internal.h"

// we just need this for purposes of unique machine id.
// So any one or two mac's is fine.
u16 hashMacAddress( PIP_ADAPTER_INFO info )
{
    u16 hash = 0;
    for ( u32 i = 0; i < info->AddressLength; i++ )
    {
        hash += ( info->Address[i] << (( i & 1 ) * 8 ));
    }
    return hash;
}

void getMacHash( u16& mac1, u16& mac2 )
{
    IP_ADAPTER_INFO AdapterInfo[32];
    DWORD dwBufLen = sizeof( AdapterInfo );

    DWORD dwStatus = GetAdaptersInfo( AdapterInfo, &dwBufLen );
    if ( dwStatus != ERROR_SUCCESS )
        return; // no adapters.

    PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;
    mac1 = hashMacAddress( pAdapterInfo );
    if ( pAdapterInfo->Next )
        mac2 = hashMacAddress( pAdapterInfo->Next );

    // sort the mac addresses. We don't want to invalidate
    // both macs if they just change order.
    if ( mac1 > mac2 )
    {
        u16 tmp = mac2;
        mac2 = mac1;
        mac1 = tmp;
    }
}

u16 getVolumeHash()
{
    DWORD serialNum = 0;

    // Determine if this volume uses an NTFS file system.
    GetVolumeInformation( "c:\\", NULL, 0, &serialNum, NULL, NULL, NULL, 0 );
    u16 hash = (u16)(( serialNum + ( serialNum >> 16 )) & 0xFFFF );

    return hash;
}

u16 getCpuHash()
{
    int cpuinfo[4] = { 0, 0, 0, 0 };
    __cpuid( cpuinfo, 0 );
    u16 hash = 0;
    u16* ptr = (u16*)(&cpuinfo[0]);
    for ( u32 i = 0; i < 8; i++ )
        hash += ptr[i];

    return hash;
}

const char* getMachineName()
{
    static char computerName[1024];
    DWORD size = 1024;
    GetComputerName( computerName, &size );
    return &(computerName[0]);
}