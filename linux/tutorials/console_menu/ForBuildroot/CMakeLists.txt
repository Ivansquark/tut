cmake_minimum_required(VERSION 3.18)
set(PROJECT consolemenu)
project(${PROJECT})

#set(CMAKE_CXX_COMPILER /bin/g++)



#target_compile_options(a.out PRIVATE -save-temps -fverbose-asm)
#set(SRCS src/main.cpp src/*.cpp src/*.c)
#set(PROJECT_FILES ${SRCS})
include_directories(inc /usr/include/)
add_definitions("-Wall -Wextra -Wpedantic -g3 -O0 -fno-elide-constructors
-std=c++17")
file(GLOB_RECURSE SRCS src/*.cpp src/*.c)

add_executable(${PROJECT} ${SRCS})

add_custom_command(
    TARGET ${PROJECT}
    COMMAND ${CMAKE_OBJDUMP} -D ${PROJECT} > ${PROJECT}.lst
)
target_link_options(${PROJECT}
    PUBLIC
    LINKER:-Map=a.map
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

#find_package( Threads)
#target_link_libraries( raw_bin ${CMAKE_THREAD_LIBS_INIT} )
