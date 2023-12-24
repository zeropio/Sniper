cmake_minimum_required(VERSION 3.27)
project(Sniper)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

# Add your source files
add_executable(Sniper
        src/main.cpp
        src/parser.cpp
        src/parser.h
        src/scanner.cpp
        src/scanner.h
        src/sniper.cpp
        src/sniper.h
)
