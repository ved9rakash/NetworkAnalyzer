cmake_minimum_required(VERSION 3.20)

project("network_analyzer" VERSION 1.0 LANGUAGES CXX)

#Set CXX standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Set different compiler options for different build
# target_compile_options(${PROJECT_NAME} PRIVATE
#     $<$<CONFIG:Debug>:-Wall -Wextra -Wpedantic -Werror>
#     $<$<CONFIG:Release>:-O3 -DNDEBUG>
# )

#Fetch Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

#ExternalProject for PcapPlusPlus
ExternalProject_Add(PcapPlusPlus
    GIT_REPOSITORY https://github.com/seladb/PcapPlusPlus.git
    GIT_TAG        v21.05 # Replace with the desired tag or commit
    PREFIX         ${CMAKE_BINARY_DIR}/PcapPlusPlus
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${CMAKE_COMMAND} -S ${CMAKE_BINARY_DIR}/PcapPlusPlus/src/PcapPlusPlus -B ${CMAKE_BINARY_DIR}/PcapPlusPlus/build -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR> -DCMAKE_BUILD_TYPE=Release
    BUILD_IN_SOURCE TRUE
    INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/PcapPlusPlus/build --target install
)

#Fetch libpcap
#FetchContent_Declare(
#    libpcap
#    GIT_REPOSITORY https://github.com/the-tcpdump-group/libpcap.git
#    GIT_TAG        libpcap-1.10.1 # Replace with the desired tag or commit
#    PREFIX         ${CMAKE_BINARY_DIR}/libpcap
#    INSTALL_DIR    ${CMAKE_BINARY_DIR}/libpcap-install
#    CMAKE_ARGS     -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
#)
#FetchContent_GetProperties(libpcap)
#if(NOT libpcap_POPULATED)
#    FetchContent_Populate(libpcap)
#    # Note: libpcap might not be set up to be used with FetchContent out-of-the-box.
#    # You might need to add additional CMake configuration or use a fork that is prepared for it.
#    add_subdirectory(${libpcap_SOURCE_DIR} ${libpcap_BINARY_DIR})
#endif()

#Include directories
include_directories(${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/)

#Include sub-directories 
add_subdirectory("src")
add_subdirectory("tests")

add_dependencies(network_analyzer PcapPlusPlus)

# Find and link PcapPlusPlus libraries
find_library(PCAPPLUSPLUS_LIB Packet++ PATHS ${CMAKE_BINARY_DIR}/PcapPlusPlus/lib NO_DEFAULT_PATH)
find_library(PCAP_LIB Pcap PATHS ${CMAKE_BINARY_DIR}/PcapPlusPlus/lib NO_DEFAULT_PATH)
target_link_libraries(network_analyzer ${PCAPPLUSPLUS_LIB} ${PCAP_LIB})

# If PcapPlusPlus requires additional dependencies, link them as well
# For example, on Unix-like systems, you might need to link pthread and libpcap:
find_package(Threads REQUIRED)
find_library(LIBPCAP_LIB pcap)
target_link_libraries(network_analyzer ${PCAPPLUSPLUS_LIB} ${PCAP_LIB} Threads::Threads ${LIBPCAP_LIB})