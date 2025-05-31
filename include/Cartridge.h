//
// Created by Jack Sangl on 2/22/25.
//

#ifndef CARTRIDGE_H
#define CARTRIDGE_H
#include <string>
#include <vector>
#include <memory>
#include "Mapper.h"
#include "Mapper_000.h"


class Cartridge {
public:
	Cartridge(const std::string& sFileName);
	~Cartridge();

private:
	std::vector<uint8_t> vPRGMemory;
	std::vector<uint8_t> vCHRMemory;

	uint8_t nMapperID = 0; // Mapper ID for the cartridge
	uint8_t nPRGBanks= 0;
	uint8_t nCHRBanks= 0;

	std:: shared_ptr<Mapper> pMapper;
	
	bool bImageValid = false; // Flag to track if cartridge image is valid

public:
	// connect to 6502
	bool cpuRead(uint16_t addr, uint8_t &data);
	bool cpuWrite(uint16_t addr, uint8_t data);

	// connect to ppu bus
	bool ppuRead(uint16_t addr, uint8_t &data);
	bool ppuWrite(uint16_t addr, uint8_t data);
	
	// Method to check if cartridge image is valid
	bool ImageValid() const;
};



#endif //CARTRIDGE_H
