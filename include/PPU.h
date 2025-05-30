//
// Created by Jack Sangl on 2/22/25.
//

#ifndef PPU_H
#define PPU_H
#include <cstdint>
#include <array>
#include "Cartridge.h"
#include "olc6502.h"
#include "Bus.h"


class PPU {
public:
	PPU();
	~PPU();

	// connect to 6502
	uint8_t cpuRead(uint16_t addr, bool rdonly = false);
	void cpuWrite(uint16_t addr, uint8_t data);

	// connect to ppu bus
	uint8_t ppuRead(uint16_t addr, bool rdonly = false);
	void ppuWrite(uint16_t addr, uint8_t data);

	void ConnectCartidge(const std::shared_ptr<Cartridge>& cartidge);
	void clock();

private:
	std::shared_ptr<Cartridge> cart;

	// name tables VRAM
	uint8_t tblName[2][1024];
	// palletes VRAM
	uint8_t tblPalette[32];

	// not needed for now
	uint8_t tblPattern[2][4096];
	// not needed for now
};



#endif //PPU_H
