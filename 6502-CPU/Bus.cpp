//
// Created by Jack Sangl on 2/13/25.
//

#include "Bus.h"

Bus::Bus() {
  // clear memory in ram
  for (auto &i : ram) i = 0x00;
  //connect CPU to bus
  cpu.ConnectBus(this);
  }

Bus:: ~Bus() {
  }

void Bus::write(uint16_t addr, uint8_t data) {
  if (addr >= 0x0000 && addr <= 0x0FFF) {
    ram[addr] = data;
  }
}
uint8_t Bus::read(uint16_t addr, bool bReadOnly) {
  if (addr >= 0x0000 && addr <= 0x0FFF) {
    ram[addr];
  }
  return 0x00;
}