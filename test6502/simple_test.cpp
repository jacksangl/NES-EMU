#include "olc6502.h"
#include "Bus.h"
#include <iostream>

int main() {
    Bus bus;
    olc6502 cpu;
    cpu.ConnectBus(&bus);

    // Simple test program: LDA #$42, NOP, JMP $0400 (infinite loop)
    bus.cpuWrite(0x0400, 0xA9); // LDA #$42
    bus.cpuWrite(0x0401, 0x42);
    bus.cpuWrite(0x0402, 0xEA); // NOP
    bus.cpuWrite(0x0403, 0x4C); // JMP $0400
    bus.cpuWrite(0x0404, 0x00);
    bus.cpuWrite(0x0405, 0x04);

    // Set reset vector to point to our test program
    bus.cpuWrite(0xFFFC, 0x00);
    bus.cpuWrite(0xFFFD, 0x04);

    cpu.reset();

    std::cout << "Starting simple CPU test..." << std::endl;
    std::cout << "Initial state: PC=$" << std::hex << cpu.pc 
              << " A=$" << (int)cpu.a << " Status=$" << (int)cpu.status << std::endl;

    // Run a few cycles
    for (int i = 0; i < 10; i++) {
        cpu.clock();
        if (cpu.complete()) {
            std::cout << "Cycle " << i << ": PC=$" << std::hex << cpu.pc 
                      << " A=$" << (int)cpu.a << " Status=$" << (int)cpu.status << std::endl;
        }
    }

    return 0;
} 