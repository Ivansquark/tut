cmake_minimum_required(VERSION 3.18)
set(PROJECT app2)
project(${PROJECT})

add_definitions("-Wall -Wextra -Wpedantic -g3 -O2 -fno-elide-constructors")

include_directories(inc)
file(GLOB_RECURSE SRCS src/*.cpp src/*.c)

add_executable(${PROJECT} ${SRCS})

target_link_options(${PROJECT}
    PUBLIC
    LINKER:-Map=${PROJECT}.map
)

install(TARGETS ${PROJECT} DESTINATION bin)

add_custom_command(
    TARGET ${PROJECT}
    POST_BUILD
    COMMAND  echo -------------------------------
    COMMAND  echo --------- POSTBUILD -----------
    COMMAND  echo -------------------------------
    COMMAND  echo ${CMAKE_CURRENT_BINARY_DIR}/
    #COMMAND sleep 20
    #COMMAND ${CMAKE_SIZE} ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT}
    #COMMAND "${CMAKE_SIZE} ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT}"
    #COMMAND ${CMAKE_OBJDUMP} -D ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT} > ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT}.asm
)


#find_package( Threads)
#target_link_libraries( raw_bin ${CMAKE_THREAD_LIBS_INIT} )
