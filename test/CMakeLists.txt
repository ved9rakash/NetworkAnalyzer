enable_testing()

# find_package(GTest REQUIRED)

#collect all the source file
file(GLOB_RECURSE TEST_SOURCES "*.cpp" ${PROJECT_SOURCE_DIR}/src)

# include_directories(${PROJECT_SOURCE_DIR}/include/learntools)
#Adding executable
add_executable(${PROJECT_NAME}_test ${TEST_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/ ${gtest_SOURCE_DIR})
#Link the executable
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME}_lib gtest_main gtest)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)
#Add test
# add_test(NAME ${PROJECT_NAME}_TEST COMMAND ${PROJECT_NAME}_test)