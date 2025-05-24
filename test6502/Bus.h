//
// Created by Jack Sangl on 4/25/25.
//

#ifndef BUS_H
#define BUS_H

// Bus.h  (stub for functional tests)
#pragma once
#include <array>
#include <cstdint>

class Bus {
public:
	std::array<uint8_t, 0x10000> ram{};   // flat 64 KB RAM

	uint8_t cpuRead(uint16_t addr, bool /*ro*/) {
		return ram[addr];
	}
	void cpuWrite(uint16_t addr, uint8_t data) {
		ram[addr] = data;
	}
};

#endif //BUS_H
