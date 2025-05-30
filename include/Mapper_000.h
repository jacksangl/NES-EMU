//
// Created by Jack Sangl on 5/30/25.
//

#ifndef MAPPER_H
#define MAPPER_H
#include "Mapper.h"


class Mapper_000 : public Mapper {
public:
	Mapper_000(uint8_t prgBanks, uint8_t chrBanks);
	~Mapper_000();
public:
	bool cpuMapRead(uint16_t addr, uint32_t &mapped_addr) override;
	bool cpuMapWrite(uint16_t addr, uint32_t &mapped_addr) override;
	bool ppuMapWrite(uint16_t addr, uint32_t &mapped_addr) override;
	bool ppuMapRead(uint16_t addr, uint32_t &mapped_addr) override;
protected:
	uint8_t nPRGBanks = 0;
	uint8_t nCHRBanks = 0;
};



#endif //MAPPER_H
