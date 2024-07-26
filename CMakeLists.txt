# CMakeLists.txt 
# Adding custom target 
add_custom_target(clear
  COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}
  COMMENT "Clean Build"
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

cmake_minimum_required(VERSION 3.20)
project("network_analyzer" VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Packages
find_package(PcapPlusPlus REQUIRED)
find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

# Package include and linkdirectories
include_directories($ENV{PCAPPP_INCLUDE_DIR})
link_directories($ENV{PCAPPP_LIB_DIR})

include_directories($ENV{Qt5_INCLUDE_DIR})
link_directories($ENV{Qt5_LIB_DIR})

# Project source and headers details
set(PROJECT_DIR_HEADERS      ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})
set(PROJECT_DIR_GUI_HEADERS  ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/gui)
set(PROJECT_DIR_SOURCES      ${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME})
set(PROJECT_DIR_GUI_SOURCES  ${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME}/gui)
# .h generated files from .ui by CMake
set(PROJECT_UI_HEADERS_GENERATED ${PROJECT_SOURCE_DIR}/cmake/build-debug/src/${PROJECT_NAME}_autogen/include/)

# Check if the directory exists
# if(NOT EXISTS ${PROJECT_DIR_UI_HEADERS})
#     message(FATAL_ERROR "The directory ${PROJECT_DIR_UI_HEADERS} does not exist. Please ensure it is generated correctly.")
# else()
#     message(STATUS "The directory ${PROJECT_DIR_UI_HEADERS} exists.")
# endif()

# Directory might be used by src/ , test/ and more.
include_directories(${PROJECT_DIR_HEADERS})
include_directories(${PROJECT_DIR_GUI_HEADERS})
include_directories(${PROJECT_UI_HEADERS_GENERATED})

# Include sub-directories 
add_subdirectory("src")

# Link libraries
target_link_libraries(${PROJECT_NAME} 
  PcapPlusPlus::Packet++ 
  PcapPlusPlus::Pcap++
  Qt5::Widgets
  Qt5::Charts
  )
