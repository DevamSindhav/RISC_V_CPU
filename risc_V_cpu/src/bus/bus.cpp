#include "bus.h"

Bus::Bus(Memory& memInstance) : ram(memInstance){}

uint8_t Bus::readByte(uint32_t address) {
	return ram.readByte(address);
}

uint32_t Bus::readWord(uint32_t address) {
	return ram.readWord(address);
}

void Bus::writeByte(uint32_t address, uint8_t value) {
	ram.writeByte(address, value);
}

void Bus::writeWord(uint32_t address, uint32_t value) {
	ram.writeWord(address, value);
}