cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

project(parser)

set(exe_name ${PROJECT_NAME})

if (MSVC)    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(${exe_name} main.cpp  "tuplePrint.h" "ImprovedParser.h")


