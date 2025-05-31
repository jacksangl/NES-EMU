//
// Created by Jack Sangl on 5/30/25.
//

#include "Mapper.h"

Mapper::Mapper(uint8_t prgBanks, uint8_t chrBanks) {
	nPRGBanks = prgBanks;
	nCHRBanks = chrBanks;
}

Mapper::~Mapper() {
	// Destructor implementation
}