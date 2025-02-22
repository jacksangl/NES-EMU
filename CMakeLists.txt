cmake_minimum_required(VERSION 3.0)
project(NES)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_executable(NES
        6502-CPU/olc6502.cpp
        6502-CPU/olc6502.h
        6502-CPU/Bus.cpp
        6502-CPU/Bus.h
        6502-CPU/PPU.cpp
        6502-CPU/PPU.h
        6502-CPU/Cartridge.cpp
        6502-CPU/Cartridge.h
)
