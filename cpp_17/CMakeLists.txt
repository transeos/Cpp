cmake_minimum_required(VERSION 3.2)
project(Cpp_17_UnitTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-ggdb3 -DDEBUG -pthread -std=c++0x -fno-inline")
#set(CMAKE_CXX_FLAGS "-O3 -pthread -std=c++0x -fno-inline")

# include
include_directories(include)

# source flies
file(GLOB MISCELLANEOUS_FILE src/miscellaneous.cpp src/miscellaneous2.cpp)
file(GLOB TEMPLATE_FILE src/template.cpp)
file(GLOB LAMBDA_FILE src/lambda.cpp)
file(GLOB LIBRARY_MISCELLANEOUS_FILE src/library_miscellaneous.cpp)

# create executables
add_executable(miscellaneous ${MISCELLANEOUS_FILE})
add_executable(templateVariadic ${TEMPLATE_FILE})
add_executable(lambda ${LAMBDA_FILE})
add_executable(library_miscellaneous ${LIBRARY_MISCELLANEOUS_FILE})
