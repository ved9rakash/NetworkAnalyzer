#Collecting all executable files 
file(GLOB_RECURSE SOURCES "*.cpp")

#Including directories 
include_directories(${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})

add_library(${PROJECT_NAME}_lib ${SOURCES})
#Defining the executable
add_executable(${PROJECT_NAME} ${SOURCES})

#Set the flags according to build type
# target_compile_options(${PROJECT_NAME} PRIVATE
#     $<$<CONFIG:Debug>:-Wall -Wextra -Wpedantic -Werror>
#     $<$<CONFIG:Release>:-O3 -DNDEBUG>
# )

# Link libraries if needed
# target_link_libraries(${PROJECT_NAME} some_library)