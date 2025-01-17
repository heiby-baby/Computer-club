cmake_minimum_required(VERSION 3.10)

project(ComputerClub)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

add_library(timeUtils ${SRC_DIR}/timeUtils.cpp)

add_executable(main ${SRC_DIR}/main.cpp)

target_link_libraries(main timeUtils)

set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)

add_executable(test_timeUtils ${TEST_DIR}/test_timeUtils.cpp)
target_link_libraries(test_timeUtils timeUtils)

enable_testing()
