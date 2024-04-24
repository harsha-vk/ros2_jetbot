cmake_minimum_required(VERSION 3.20)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(jetbot_controller C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

pico_sdk_init()

include_directories(
    include
    lib/include
)

add_executable(${PROJECT_NAME} 
    src/init.cpp
    src/interrupts.cpp
    src/main.cpp
    src/serialization.cpp
    src/speed_manager.cpp
    lib/src/i2c_slave.cpp
    lib/src/pid.cpp
    lib/src/wire.cpp
)

pico_add_extra_outputs(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} 
    pico_stdlib
    hardware_i2c
    hardware_pwm
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)
