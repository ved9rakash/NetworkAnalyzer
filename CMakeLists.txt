# CMakeLists.txt 
cmake_minimum_required(VERSION 3.20)
project("network_analyzer" VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project source and headers details
set(PROJECT_DIR_HEADERS ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})
set(PROJECT_DIR_SOURCES ${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME})

# Packages
find_package(PcapPlusPlus REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Package include directories
include_directories($ENV{PCAPPP_INCLUDE_DIR})
include_directories($ENV{Qt5_INCLUDE_DIR})

# Package link directories
link_directories($ENV{PCAPPP_LIB_DIR})
link_directories($ENV{Qt5_LIB_DIR})

# Directory might be used by src/ , test/ and more.
include_directories("${PROJECT_SOURCE_DIR}/cmake/build-debug/src/${PROJECT_NAME}_autogen/include/")
include_directories(${PROJECT_DIR_HEADERS})

# Include sub-directories 
add_subdirectory("src")

# Link libraries
target_link_libraries(${PROJECT_NAME} 
  PcapPlusPlus::Packet++ 
  PcapPlusPlus::Pcap++
  Qt5::Widgets
  )