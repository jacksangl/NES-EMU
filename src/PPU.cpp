//
// Created by Jack Sangl on 2/22/25.
//

#include "PPU.h"


// connect to 6502
uint8_t PPU::cpuRead(uint16_t addr, bool rdonly) {
	uint8_t data = 0x00;

	switch (addr)
	{
		case 0x0000: // Control
			break;
		case 0x0001: // Mask
			break;
		case 0x0002: // Status
			break;
		case 0x0003: // OAM Address
			break;
		case 0x0004: // OAM Data
			break;
		case 0x0005: // Scroll
			break;
		case 0x0006: // PPU Address
			break;
		case 0x0007: // PPU Data
			break;
	}
return data;
}
void PPU::cpuWrite(uint16_t addr, uint8_t data) {
	switch (addr)
	{
		case 0x0000: // Control
			break;
		case 0x0001: // Mask
			break;
		case 0x0002: // Status
			break;
		case 0x0003: // OAM Address
			break;
		case 0x0004: // OAM Data
			break;
		case 0x0005: // Scroll
			break;
		case 0x0006: // PPU Address
			break;
		case 0x0007: // PPU Data
			break;
	}
}

// connect to ppu bus
uint8_t PPU::ppuRead(uint16_t addr, bool rdonly) {
	uint8_t data = 0x00;
	addr &= 0x3FFF;

	if (cart->ppuRead(addr, data)) {

	}
	return data;

}
void PPU::ppuWrite(uint16_t addr, uint8_t data) {
	addr &= 0x3FFF;
	if (cart->ppuWrite(addr, data)) {

	}
	return;
}

void PPU::ConnectCartidge(const std::shared_ptr<Cartridge>& cartridge) {
	this->cart = cartridge;
	return;
}