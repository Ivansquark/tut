cmake_minimum_required(VERSION 3.28)

# Set project name
project(BuzzTest)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)

# Specify the cross-compilation toolchain file
# (This will use the toolchain file you created earlier)
if (NOT CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/toolchain-arm-linux-gnueabi.cmake)
endif()

# Find GoogleTest
find_package(GTest REQUIRED)

# Include directories
include_directories(${GTEST_INCLUDE_DIRS})

# Source files for testing
set(SOURCES
    buzz_test.cpp  # Include the test source file
)

# Executable for tests
add_executable(buzz_test ${SOURCES})

# Link the Google Test and pthread libraries
target_link_libraries(buzz_test ${GTEST_LIBRARIES} pthread)

# Enable testing
enable_testing()

# Add unit tests
add_test(NAME BuzzDriverTest COMMAND buzz_test)
