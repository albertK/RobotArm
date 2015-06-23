cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(RobotArm)

set(DAQ_INCLUDE_DIR /home/albert/Lib/ixpio/include)
set(DAQ_LINK_DIR /home/albert/Lib/ixpio/lib)
set(DAQ_LINK_LIB_AO pio_64)
set(DAQ_LINK_LIB_ENC enc600_64)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${DAQ_INCLUDE_DIR})
link_directories(${DAQ_LINK_DIR})

#build the library AnalogOutput
add_library(AnalogOutput ${CMAKE_CURRENT_SOURCE_DIR}/src/rcl/hardware/analog_output.cpp)
target_link_libraries(AnalogOutput ${DAQ_LINK_LIB_AO} ${DAQ_LINK_LIB_AO})

#build the library Encoder
add_library(Encoder ${CMAKE_CURRENT_SOURCE_DIR}/src/rcl/hardware/encoder.cpp)
target_link_libraries(Encoder ${DAQ_LINK_LIB_ENC})

#build the library MotorJoint
add_library(MotorJoint ${CMAKE_CURRENT_SOURCE_DIR}/src/rcl/basic_utility/motor_joint.cpp)
target_link_libraries(MotorJoint Encoder AnalogOutput)

