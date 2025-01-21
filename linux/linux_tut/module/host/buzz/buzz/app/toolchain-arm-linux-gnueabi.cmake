# Set the cross-compilation toolchain
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Specify the cross compiler executables
set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)

# Set the sysroot (if applicable, replace this with your sysroot path)
set(CMAKE_SYSROOT /usr/bin/)

# Optionally specify the find paths for libraries and headers
set(CMAKE_FIND_ROOT_PATH /usr/arm-linux-gnueabihf/)

# Make sure we link against the ARM libraries
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)

