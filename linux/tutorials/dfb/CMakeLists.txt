cmake_minimum_required(VERSION 3.18)
set(PROJECT a)
project(${PROJECT})
if (UNIX)
    set(CMAKE_CXX_COMPILER /usr/bin/g++)
endif (UNIX)
if (WIN32)
    set(CMAKE_CXX_COMPILER C:/TDM-GCC-64/bin/g++.exe)
endif (WIN32)

#target_compile_options(a.out PRIVATE -save-temps -fverbose-asm)
#set(SRCS src/main.cpp src/*.cpp src/*.c)
#set(PROJECT_FILES ${SRCS})
include_directories(inc/)
add_definitions("-Wall -Wextra -Wpedantic -g3 -O0 -fno-elide-constructors
-std=c++23")
file(GLOB_RECURSE SRCS src/*.cpp src/*.c)

add_compile_options(-fsanitize=address,undefined)
add_link_options(-fsanitize=address,undefined)

add_executable(${PROJECT}.out ${SRCS})

add_custom_command(
    TARGET ${PROJECT}.out
    COMMAND ${CMAKE_OBJDUMP} -D ${PROJECT}.out > ${PROJECT}.lst
)
target_link_options(a.out
    PUBLIC
    LINKER:-Map=a.map
)

#find_package( Threads)
#target_link_libraries( raw_bin ${CMAKE_THREAD_LIBS_INIT} )
