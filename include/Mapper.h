//
// Created by Jack Sangl on 5/30/25.
//

#ifndef MAPPER_H
#define MAPPER_H
#include <cstdint>

class Mapper {
public:
	Mapper(uint8_t prgBanks, uint8_t chrBanks);
	~Mapper();
public:
	virtual bool cpuMapRead(uint16_t addr, uint32_t &mapped_addr) = 0;
	virtual bool cpuMapWrite(uint16_t addr, uint32_t &mapped_addr) = 0;
	virtual bool ppuMapRead(uint16_t addr, uint32_t &mapped_addr) = 0;
	virtual bool ppuMapWrite(uint16_t addr, uint32_t &mapped_addr) = 0;
protected:
	uint8_t nPRGBanks = 0;
	uint8_t nCHRBanks = 0;
};



#endif //MAPPER_H
