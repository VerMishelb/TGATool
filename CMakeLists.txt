cmake_minimum_required(VERSION 3.30)

# Static linking of vcruntime
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(TGATool LANGUAGES CXX
    VERSION 1.4.3.1
    DESCRIPTION "A tool for converting CIU TGA files to readable format and back."
    HOMEPAGE_URL "https://github.com/VerMishelb/TGATool"
)

add_executable(TGATool main.cpp)
# Precaution measures for msvc compiler not caring about UTF-8 (it is said that C++26 will standardise UTF-8 for source files)
target_compile_options(TGATool
    PUBLIC
    "$<$<C_COMPILER_ID:MSVC>:/utf-8>"
    "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>"
)
