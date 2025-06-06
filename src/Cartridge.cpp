//
// Created by Jack Sangl on 2/22/25.
//

#include <fstream>
#include <iostream>
#include "Cartridge.h"

bool Cartridge::cpuRead(uint16_t addr, uint8_t &data) {
	uint32_t mapped_addr = 0;
	if (pMapper->cpuMapRead(addr, mapped_addr)) {
		if (mapped_addr < vPRGMemory.size()) {
			data = vPRGMemory[mapped_addr];
			return true;
		}
	}
	return false;
}
bool Cartridge::cpuWrite(uint16_t addr, uint8_t data) {
	uint32_t mapped_addr = 0;
	if (pMapper->cpuMapWrite(addr, mapped_addr)) {
		if (mapped_addr < vPRGMemory.size()) {
			vPRGMemory[mapped_addr] = data;
			return true;
		}
	}
	return false;
}


bool Cartridge::ppuRead(uint16_t addr, uint8_t &data) {
	uint32_t mapped_addr = 0;
	if (pMapper->ppuMapRead(addr, mapped_addr)) {
		if (mapped_addr < vCHRMemory.size()) {
			data = vCHRMemory[mapped_addr];
			return true;
		}
	}
	return false;
}
bool Cartridge::ppuWrite(uint16_t addr, uint8_t data) {
	uint32_t mapped_addr = 0;
	if (pMapper->ppuMapWrite(addr, mapped_addr)) {
		if (mapped_addr < vCHRMemory.size()) {
			vCHRMemory[mapped_addr] = data;
			return true;
		}
	}
	return false;
}

bool Cartridge::ImageValid() const {
	return bImageValid;
}

Cartridge::Cartridge(const std::string &sFileName) {
	struct sHeader {
		uint8_t prg_rom_chunks;
		uint8_t chr_rom_chunks;
		uint8_t mapper1;
		uint8_t mapper2;
		uint8_t prg_ram_size;
		uint8_t tv_system1;
		uint8_t tv_system2;
		char unused[5];
	} header;
	
	bImageValid = false; // Initialize as invalid
	
	std:: ifstream ifs;
	ifs.open(sFileName, std::ifstream::binary);
	if (ifs.is_open()) {
		ifs.read((char*)&header, sizeof(sHeader));

		if (header.mapper1 & 0x04) {
			ifs.seekg(512, std::ios_base::cur); // Skip 512 bytes if the 4th bit of mapper1 is set
		}
		nMapperID = ((header.mapper2 >> 4) << 4) | (header.mapper1 >> 4);
		// !! TODO THIS WILL NEED TO BE CHANGED WHEN WE ADD MORE MAPPERS
		uint8_t nFileType = 1;

		if (nFileType == 0) {

		}
		if (nFileType == 1) {
			nPRGBanks = header.prg_rom_chunks;
			vPRGMemory.resize(nPRGBanks*16384);
			ifs.read((char*)vPRGMemory.data(), vPRGMemory.size());

			nCHRBanks= header.chr_rom_chunks;
			vCHRMemory.resize(nCHRBanks*8192);
			ifs.read((char*)vCHRMemory.data(), vCHRMemory.size());
		}
		if (nFileType == 2) {

		}

		switch (nMapperID) {
			case 0: pMapper = std::make_shared<Mapper_000>(nPRGBanks, nCHRBanks); break;
		}
		
		// Set as valid if we successfully loaded data and created a mapper
		if (pMapper && !vPRGMemory.empty()) {
			bImageValid = true;
		}
		
		ifs.close();
	}
}

Cartridge::~Cartridge() {
	// Destructor implementation (pMapper will be automatically cleaned up)
}
