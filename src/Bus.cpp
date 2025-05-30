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

uint8_t Bus::cpuRead(uint16_t addr, bool bReadOnly) {
    uint8_t data = 0x00;  // Default value if no read occurs
    if (cart->cpuRead(addr, data)) {

    }
    else if (addr >= 0x0000 && addr <= 0x1FFF)
        data = cpuRam[addr & 0x07FF];
    else if (addr >= 0x2000 && addr <= 0x3FFF)
        data = ppu.cpuRead(addr & 0x0007, bReadOnly);
    return data;
}

void Bus::cpuWrite(uint16_t addr, uint8_t data) {
    if (cart->cpuWrite(addr, data)) {

    }
    else if (addr >= 0x0000 && addr <= 0x1FFF)
        cpuRam[addr & 0x07FF] = data;
    else if (addr >= 0x2000 && addr <= 0x3FFF) {
        ppu.cpuWrite(addr & 0x0007, data);
    } else {
        std::cerr << "Bus write error: Address out of range: " << std::hex << addr << std::endl;
    }
}

void Bus::reset() {
    cpu.reset();
    nSystemClockCounter = 0;  // Reset system clock counter
}

void Bus::insertCartridge(const std::shared_ptr<Cartridge> &cartridge) {
    this->cart = cartridge;
    ppu.ConnectCartidge(cartridge);
}
