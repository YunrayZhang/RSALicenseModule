#include <iostream>
#include "get_machineid_external.h"

int main(int argc, char * argv[])
{
    std::string machineId = getSystemUniqueId();
    std::cout<<"machine id is->"<<machineId<<std::endl;

    /*
    bool ret = validate_machine_fp(machineId);
    std::cout<<"validate result is "<<ret<<std::endl;
     */
    return 0;
}