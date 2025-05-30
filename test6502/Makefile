# Makefile for NES Emulator Project
CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LIBPNG_CFLAGS = $(shell pkg-config --cflags libpng)
LIBPNG_LIBS = $(shell pkg-config --libs libpng)

# Add libpng flags
CXXFLAGS += $(LIBPNG_CFLAGS)
LDFLAGS += $(LIBPNG_LIBS)

# Add OpenGL and other system frameworks for macOS
LDFLAGS += -framework OpenGL -framework GLUT -framework CoreFoundation

# Source files
SOURCES = testCopied.cpp olc6502.cpp Bus.cpp
TARGET = nes_emulator

# Default target
all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS)

clean:
	rm -f $(TARGET)

# Alternative target for the simple test
simple_test: simple_test.cpp olc6502.cpp Bus.cpp
	$(CXX) $(CXXFLAGS) -o simple_test simple_test.cpp olc6502.cpp Bus.cpp $(LDFLAGS)

.PHONY: all clean simple_test 