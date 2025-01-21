# CMakeLists.txt for userspace application and unit tests

cmake_minimum_required(VERSION 3.10)
project(ButtonDriverApp)

# Specify the ARM cross-compiler toolchain
set(CROSS_COMPILE arm-linux-gnueabihf-)
set(ARCH arm)

# Set the cross compiler and linker flags
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER ${CROSS_COMPILE}gcc)
set(CMAKE_CXX_COMPILER ${CROSS_COMPILE}g++)
set(CMAKE_LINKER ${CROSS_COMPILE}ld)

# Set the C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add source files for the main application
add_executable(button_reader button_reader.cpp)

# Link necessary libraries (e.g., pthread for signal handling)
target_link_libraries(button_reader PRIVATE pthread)

# Enable testing
enable_testing()


# Unit tests for the application
add_executable(button_reader_test button_reader_test.cpp)

# Link the unit tests with GoogleTest
target_link_libraries(button_reader_test gtest gmock pthread)

# Run the tests
add_test(NAME ButtonReaderTests COMMAND button_reader_test)

# Specify the target architecture for cross-compilation
set(CMAKE_FIND_ROOT_PATH /usr/arm-linux-gnueabihf)

