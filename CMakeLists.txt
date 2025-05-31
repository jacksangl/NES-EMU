cmake_minimum_required(VERSION 3.0)
project(NES)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

find_package(OpenGL REQUIRED)
find_package(PNG REQUIRED)
find_package(GLUT REQUIRED)

add_executable(NES
        src/test.cpp
        src/Bus.cpp
        src/Cartridge.cpp
        src/6502.cpp
        src/PPU.cpp
        src/Mapper.cpp
        src/Mapper_000.cpp
        include/PPU.h
        include/6502.h
        include/Cartridge.h
        include/Bus.h
        include/Mapper_000.h
        include/olcPixelGameEngine.h
)

if(PNG_FOUND)
    target_include_directories(NES PRIVATE ${PNG_INCLUDE_DIRS})
    message(STATUS "Found libpng headers at: ${PNG_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "libpng (PNG) headers not found by find_package.")
endif()

if(GLUT_FOUND AND DEFINED GLUT_INCLUDE_DIRS)
    target_include_directories(NES PRIVATE ${GLUT_INCLUDE_DIRS})
    message(STATUS "Found GLUT headers at: ${GLUT_INCLUDE_DIRS}")
endif()

target_link_libraries(NES
        PRIVATE
        ${OPENGL_LIBRARIES}
        ${PNG_LIBRARIES}
        ${GLUT_LIBRARIES}
)

message(STATUS "Linking OpenGL libraries: ${OPENGL_LIBRARIES}")
if(PNG_FOUND)
    message(STATUS "Linking PNG libraries: ${PNG_LIBRARIES}")
endif()
if(GLUT_FOUND)
    message(STATUS "Linking GLUT libraries: ${GLUT_LIBRARIES}")
endif()

if(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    target_link_libraries(NES PRIVATE ${COCOA_LIBRARY} ${IOKIT_LIBRARY})
endif()

if(UNIX AND NOT APPLE)
    target_link_libraries(NES PRIVATE X11 GL pthread)
endif()