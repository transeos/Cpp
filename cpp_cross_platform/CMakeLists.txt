cmake_minimum_required(VERSION 3.5)
project(cpp_win VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(cpp_win src/main.cpp src/hello.cpp)
