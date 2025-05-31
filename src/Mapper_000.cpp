//
// Created by Jack Sangl on 5/30/25.
//

#include "Mapper_000.h"
#include <cstdint>


Mapper_000::Mapper_000(uint8_t prgBanks, uint8_t chrBanks) : Mapper(prgBanks, chrBanks) {
	// Initialize any specific variables for Mapper 000 if needed
}
Mapper_000::~Mapper_000() {
	// Cleanup if necessary
}
bool Mapper_000::cpuMapRead(uint16_t addr, uint32_t &mapped_addr) {
	if (addr >= 0x8000 && addr <= 0xFFFF) {
		if (nPRGBanks > 1) {
			mapped_addr = addr & 0x7FFF;
		} else {
			mapped_addr = addr & 0x3FFF; // Map to 16KB if only one PRG bank
		}
		return true;
	}
	return false;
}
bool Mapper_000::cpuMapWrite(uint16_t addr, uint32_t &mapped_addr) {
	if (addr >= 0x8000 && addr <= 0xFFFF) {
		if (nPRGBanks > 1) {
			mapped_addr = addr & 0x7FFF;
		} else {
			mapped_addr = addr & 0x3FFF; // Map to 16KB if only one PRG bank
		}
		return true;
	}
	return false;
}
bool Mapper_000::ppuMapWrite(uint16_t addr, uint32_t &mapped_addr) {
	if (addr >= 0x0000 && addr <= 0x1FFF) {
		mapped_addr = addr;
		return true;
	}
	return false;
}
bool Mapper_000::ppuMapRead(uint16_t addr, uint32_t &mapped_addr) {
	if (addr >= 0x0000 && addr <= 0x1FFF) {
		mapped_addr = addr;
		return true;
	}
	return false;
}