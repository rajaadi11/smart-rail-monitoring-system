
cmake_minimum_required(VERSION 3.16)

project(RailCANCommunication)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(can_simulator
    src/main.cpp
    src/can_frame.cpp
)

target_include_directories(can_simulator PRIVATE
    include
)

target_compile_options(can_simulator PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
