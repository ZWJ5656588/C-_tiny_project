cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17) #让Cmake编译时支持C++17标准

file(COPY ${CMAKE_CURRENT_SOURCE_DIR} computerRoom.txt
 DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

project(RESERVE_CPU_ROOM)

add_executable(reserve_cpu_room identity.h student.h manager.h teacher.h globalfile.h computerRoom.h order_file.h
 manager.cpp menu.cpp student.cpp teacher.cpp orderfile.cpp) 
