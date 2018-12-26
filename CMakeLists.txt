cmake_minimum_required(VERSION 3.09)
project(RsaLicenseLib)

set(CMAKE_CXX_STANDARD 14)
#set(RSA_INCLUDE /Users/zhangyl-j/cryptopp)

#include_directories(${RSA_INCLUDE})

#find_library(${RSA_INCLUDE}/cmake-build-debug cryptopp)

add_library(RsaLicenseLib biginteger.h biginteger.cpp rsalicense.cpp rsalicense.h)

project(RSALicenseMaker)
include_directories(CMAKE_CURRENT_LIST)
link_libraries(RsaLicenseLib)
add_executable(RSALicenseMaker makelicense.cpp)

project(RSADecoder)
include_directories(CMAKE_CURRENT_LIST)
link_libraries(RsaLicenseLib)
add_executable(RSADecoder application_example.cpp)

project(GetMachineFingerPrint)
set(HEADER getmachineid_internal.h get_machineid_external.h)
if (WIN32)
    link_libraries(IPHLPAPI)
    set(SOURCE get_machineid_win.cpp)
else()
    set(SOURCE get_machineid_unix.cpp)
endif()
add_executable(GetMachineFP ${HEADER} ${SOURCE} get_machineid_main.cpp get_machineid.cpp)

