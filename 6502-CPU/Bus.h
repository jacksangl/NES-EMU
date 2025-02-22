//
// Created by Jack Sangl on 2/13/25.
//

#ifndef BUS_H
#define BUS_H
#include "olc6502.h"
#include <array>

class olc6502;

class Bus {
public:
    Bus();
    ~Bus();
public:
    olc6502 cpu;
    // fake ram
    std::array<uint8_t, 64*1024> ram;

public: //Bus read and write
	void write(uint16_t addr, uint8_t data);
    uint8_t read(uint16_t addr, bool bReadOnly = false);
};



#endif //BUS_H
