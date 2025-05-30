#include "Bus.h"
#include "olc6502.h"  // Now include olc6502.h here instead
#include <fstream>
#include <iostream>

Bus::Bus() {
    // Initialize RAM to 0x00
    // Connect CPU to communication bus
    cpu.ConnectBus(this);

    // Clear RAM contents, just in case :P
    for (auto &i : ram) i = 0x00;
}

uint8_t Bus::cpuRead(uint16_t addr, bool /*ro*/) {
    if (addr >= 0x0000 && addr <= 0xFFFF)
        return ram[addr];
    return 0x00;
}

void Bus::cpuWrite(uint16_t addr, uint8_t data) {
    if (addr >= 0x0000 && addr <= 0xFFFF)
        ram[addr] = data;
}

bool Bus::loadROM(const std::string& filePath, uint16_t startAddress) {
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open ROM file: " << filePath << std::endl;
        return false;
    return true;
    }
    
    // Get file size
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    
    // Check if ROM fits in memory
    if (startAddress + size > 0x10000) {
        std::cerr << "Error: ROM too large to fit in memory at address 0x" 
                  << std::hex << startAddress << std::endl;
        file.close();
        return false;
    }
    
    // Read ROM data directly into RAM
    if (!file.read(reinterpret_cast<char*>(&ram[startAddress]), size)) {
        std::cerr << "Error: Failed to read ROM file: " << filePath << std::endl;
        file.close();
        return false;
    }
    
    file.close();
    std::cout << "Successfully loaded ROM: " << filePath 
              << " (" << std::dec << size << " bytes) at address 0x" 
              << std::hex << startAddress << std::endl;
    return true;
}