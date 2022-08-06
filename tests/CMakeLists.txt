cmake_minimum_required(VERSION 3.22)
project(SudokuSolver_tests)

# Download gtest
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(SudokuSolver_tests SudokuSolver_tests.cpp)

target_link_libraries(SudokuSolver_tests SudokuSolver GTest::gtest_main)

target_include_directories(SudokuSolver_tests PUBLIC ${CMAKE_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(SudokuSolver_tests)