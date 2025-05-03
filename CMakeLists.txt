cmake_minimum_required(VERSION 3.27)
project(cpplox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(cpplox main.cpp
        common.hpp
        debug.hpp
        debug.cpp
        value.hpp
        chunk.hpp
        chunk.cpp
        value.cpp
        vm.hpp
        vm.cpp
        compiler.hpp
        compiler.cpp
        scanner.hpp
        scanner.cpp
)
