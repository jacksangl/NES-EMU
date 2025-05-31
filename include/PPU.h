//
// Created by Jack Sangl on 2/22/25.
//

#ifndef PPU_H
#define PPU_H
#include <cstdint>
#include <array>
#include <memory>
#include "olcPixelGameEngine.h"

// Forward declarations to avoid circular dependencies
class Cartridge;
class Bus;
class MOS6502;

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
	olc::Pixel palScreen[0x40];
	
	// Sprite pointers for dynamic allocation
	olc::Sprite* sprScreen; // 256x240 pixel screen
	olc::Sprite* sprNameTable[2]; // 2 name tables
	olc::Sprite* sprPatternTable[2]; // 2 pattern tables

public:
	// Method names to match usage in test.cpp
	olc::Sprite& GetScreen();
	olc::Sprite& getScreen(); // Keep both for compatibility
	olc::Sprite& getNameTable(uint8_t i);
	olc::Sprite& getPatternTable(uint8_t i);
	bool frame_complete = false; // frame complete flag

private:
	int16_t scanline = 0; // current scanline
	int16_t cycle = 0; // current cycle

};



#endif //PPU_H
