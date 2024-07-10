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

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

#Include directories
include_directories(${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/)

#Include sub-directories 
add_subdirectory("src")
add_subdirectory("tests")