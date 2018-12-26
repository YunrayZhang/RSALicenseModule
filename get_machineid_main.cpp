#include <iostream>
#include "get_machineid_external.h"

int main(int argc, char * argv[])
{
    std::string machineId = getSystemUniqueId();
    std::cout<<"machine id is "<<machineId<<std::endl;
    return 0;
}