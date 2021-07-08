cmake_minimum_required(VERSION 3.2)
project(Cpp_17_UnitTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-ggdb3 -DDEBUG -std=c++17 -fno-inline -ltbb")

find_package(TBB REQUIRED)

# include
include_directories(include)

# source flies
file(GLOB MISCELLANEOUS_FILE src/miscellaneous.cpp src/miscellaneous2.cpp)
file(GLOB TEMPLATE_FILE src/template.cpp)
file(GLOB LAMBDA_FILE src/lambda.cpp)
file(GLOB LIBRARY_MISCELLANEOUS_FILE src/library_miscellaneous.cpp)
file(GLOB PARALLEL_FILE src/parallel.cpp)

# create executables
add_executable(miscellaneous ${MISCELLANEOUS_FILE})
add_executable(templateVariadic ${TEMPLATE_FILE})
add_executable(lambda ${LAMBDA_FILE})
add_executable(library_miscellaneous ${LIBRARY_MISCELLANEOUS_FILE})

add_executable(parallel ${PARALLEL_FILE})
target_link_libraries(parallel ${TBB_IMPORTED_TARGETS})
