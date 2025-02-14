cmake_minimum_required(VERSION 3.10)

project(CompClub)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(SOURCES
    src/GameClub.cpp
    src/main.cpp
    src/timeUtils.cpp
)

add_executable(CompClub ${SOURCES})

# Копирование файлов из data в папку debug
add_custom_command(
    TARGET CompClub POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data
    $<TARGET_FILE_DIR:CompClub>/data
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Тесты
# Указываем список тестовых файлов
set(TEST_SOURCES
    src/tests/test_timeUtils.cpp
    src/tests/test_gameClub.cpp
)

add_executable(unit_test ${TEST_SOURCES} src/timeUtils.cpp src/GameClub.cpp)

target_link_libraries(
  unit_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_test)