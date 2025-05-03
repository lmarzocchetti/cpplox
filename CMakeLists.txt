cmake_minimum_required(VERSION 3.27)
project(cpplox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(cpplox main.cpp
        src/common.hpp
        src/debug.hpp
        src/debug.cpp
        src/value.hpp
        src/chunk.hpp
        src/chunk.cpp
        src/value.cpp
        src/vm.hpp
        src/vm.cpp
        src/compiler.hpp
        src/compiler.cpp
        src/scanner.hpp
        src/scanner.cpp
)
