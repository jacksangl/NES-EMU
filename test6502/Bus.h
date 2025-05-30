//
// Created by Jack Sangl on 4/25/25.
//

#ifndef BUS_H
#define BUS_H

// Bus.h  (stub for functional tests)
#pragma once
#include <array>
#include <cstdint>
#include <string>
#include "olc6502.h"
#include "PPU.h"

class Bus {
public:
	std::array<uint8_t,2048> cpuRam;   // flat 64 KB RAM

	PPU ppu;  // PPU instance

	olc6502 cpu;

	Bus();  // Move implementation to .cpp file
	
	// TODO remove the & 0x07FF after the functional test and the if statement
	uint8_t cpuRead(uint16_t addr, bool /*ro*/);
	void cpuWrite(uint16_t addr, uint8_t data);
};

#endif //BUS_H