cmake_minimum_required(VERSION 3.18)

set(PROJECT main)

project(${PROJECT})

set(EXECUTABLE_NAME ${PROJECT})
set(CMAKE_CXX_FLAGS "-pthread -std=c++20 -g3 -O0 -Wall -ffunction-sections -fdata-sections")
#set(CMAKE_LDFLAGS "-std=c++20 -Xlinker -Map${PROJECT}.map")

include_directories(inc/)

file(GLOB SOURCES src/*.cpp)

add_executable(${PROJECT} ${SOURCES})

target_link_libraries(${PROJECT} pthread)

#set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_CXX_COMPILER> -o ${PROJECT_NAME}  <OBJECTS>  ${CMAKE_LD_FLAGS}")
