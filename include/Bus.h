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
	Bus();
	~Bus();

	std::array<uint8_t,2048> cpuRam;   // flat 64 KB RAM

	PPU ppu;  // PPU instance
	olc6502 cpu;

	std::shared_ptr<Cartridge> cart;

	// TODO remove the & 0x07FF after the functional test and the if statement
	// TODO I THINK THIS DOESNT NEED REMOVED IDK SO IM KEEPING THIS HERE
	uint8_t cpuRead(uint16_t addr, bool /*ro*/);
	void cpuWrite(uint16_t addr, uint8_t data);

public:
	void insertCartridge(const std::shared_ptr<Cartridge>& cartridge);
	void reset();
	void clock();

private:
	uint32_t nSystemClockCounter = 0;  // System clock counter
};

#endif //BUS_H