cmake_minimum_required(VERSION 3.09)
project(RsaLicenseLib)

set(CMAKE_CXX_STANDARD 14)
set(OUTDIR ~zhangyl-j)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY output)
#set(RSA_INCLUDE /Users/zhangyl-j/cryptopp)

#include_directories(${RSA_INCLUDE})

#find_library(${RSA_INCLUDE}/cmake-build-debug cryptopp)

add_library(RsaLicenseLib STATIC src/biginteger.h src/biginteger.cpp src/rsalicense.cpp src/rsalicense.h src/Base64.h)
add_library(RsaLicenseShared SHARED src/biginteger.h src/biginteger.cpp src/rsalicense.cpp src/rsalicense.h src/Base64.h)
project(RSALicenseMaker)
include_directories(CMAKE_CURRENT_LIST ./ gtest/include)
link_libraries(RsaLicenseLib)
add_executable(RSALicenseMaker src/makelicense.cpp)

project(RSADecoder)
link_libraries(RsaLicenseLib)
add_executable(RSADecoder src/application_example.cpp)

project(GetMachineFingerPrint)
set(HEADER src/getmachineid_internal.h src/get_machineid_external.h)
if (WIN32)
    link_libraries(IPHLPAPI)
    set(SOURCE src/get_machineid_win.cpp)
else()
    set(SOURCE src/get_machineid_unix.cpp)
endif()
add_executable(GetMachineFP ${HEADER} ${SOURCE} src/get_machineid_main.cpp src/get_machineid.cpp)
install(TARGETS GetMachineFP
        RUNTIME DESTINATION ${OUTDIR})

project(unittests)
link_directories(gtest/lib)
link_libraries(gtest gtest_main)
add_executable(unittests unittest/unittests.cpp)
