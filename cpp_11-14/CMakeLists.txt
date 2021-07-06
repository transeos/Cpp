cmake_minimum_required(VERSION 3.2)
project(Cpp_11-14_UnitTest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-ggdb3 -DDEBUG -pthread -std=c++0x -fno-inline")
#set(CMAKE_CXX_FLAGS "-O3 -pthread -std=c++0x -fno-inline")

# include
include_directories(include)

# source flies
file(GLOB DECLTYPE_FILE src/decltype.cpp)
file(GLOB LAMBDA_FILE src/lambda.cpp)
file(GLOB OP_OVERLOADING_FILE src/operator_overloading.cpp)
file(GLOB SMART_PTR_FILE src/smart_ptr.cpp)
file(GLOB STATIC_ASSERT_FILE src/static_assert.cpp)
file(GLOB STL_FILE src/stl.cpp)
file(GLOB TEMPLATE_VARIADIC_FILE src/template_variadic.cpp)

file(GLOB FORWARD_FILE src/forward.cpp)
file(GLOB MOVE_FILE src/move.cpp)
file(GLOB RVALUE_LVALUE_FILE src/rvalue_lvalue.cpp)

file(GLOB MISCELLANEOUS_FILE src/miscellaneous.cpp)

# create executables
add_executable(decltype ${DECLTYPE_FILE})
add_executable(lambda ${LAMBDA_FILE})
add_executable(opOverloading ${OP_OVERLOADING_FILE})
add_executable(smartPtr ${SMART_PTR_FILE})
add_executable(staticAssert ${STATIC_ASSERT_FILE})
add_executable(stl ${STL_FILE})
add_executable(templateVariadic ${TEMPLATE_VARIADIC_FILE})

add_executable(forward ${FORWARD_FILE})
add_executable(move ${MOVE_FILE})
add_executable(rvaluelvalue ${RVALUE_LVALUE_FILE})

add_executable(miscellaneous ${MISCELLANEOUS_FILE})
