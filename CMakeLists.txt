cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(RobotArm)

set(DAQ_INCLUDE_DIR /home/albert/Lib/ixpio/include)
set(DAQ_LINK_DIR /home/albert/Lib/ixpio/lib)
set(DAQ_LINK_LIB pio_64)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${DAQ_INCLUDE_DIR})
link_directories(${DAQ_LINK_DIR})

add_executable(test src/test/test.cpp)
target_link_libraries(test ${DAQ_LINK_LIB})