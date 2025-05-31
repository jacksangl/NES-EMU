cmake_minimum_required(VERSION 3.0)
project(NES)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include_directories(include)


add_executable(NES
        src/Bus.cpp
        src/Cartridge.cpp
        src/6502.cpp
        src/PPU.cpp
        include/PPU.h
        include/6502.h
        include/Cartridge.h
        include/Bus.h
        include/Mapper_000.h
        src/Mapper_000.cpp
        include/olcPixelGameEngine.h
)
