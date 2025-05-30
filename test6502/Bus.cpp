#include "Bus.h"
#include "olc6502.h"  // Now include olc6502.h here instead
#include <fstream>
#include <iostream>

Bus::Bus() {
    // Initialize RAM to 0x00
    // Connect CPU to communication bus
    cpu.ConnectBus(this);

    // Clear RAM contents, just in case :P
    for (auto &i : cpuRam) i = 0x00;
}

uint8_t Bus::cpuRead(uint16_t addr, bool /*ro*/) {
    uint8_t data = 0x00;  // Default value if no read occurs    
    if (addr >= 0x0000 && addr <= 0x1FFF)
        data = cpuRam[addr & 0x07FF];
    return data;
}

void Bus::cpuWrite(uint16_t addr, uint8_t data) {
    if (addr >= 0x0000 && addr <= 0x1FFF)
        cpuRam[addr & 0x07FF] = data;
}

