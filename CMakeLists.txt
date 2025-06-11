cmake_minimum_required(VERSION 3.30)

# Static linking of vcruntime
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Put libs together with executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(TGATool LANGUAGES CXX
    VERSION 1.4.4.0
    DESCRIPTION "A tool for converting CIU TGA files to readable format and back."
    HOMEPAGE_URL "https://github.com/VerMishelb/TGATool"
)

# Global compiler settings
if (MSVC)
    add_compile_options("/utf-8")
endif()

# TGATool
add_executable(TGATool src/main.cpp)
target_include_directories(TGATool PUBLIC src)
if (WIN32)
    target_sources(TGATool PRIVATE TGATool.exe.manifest)
endif()
