#pragma once

#include "../memory/memory.h"
#include <cstdint>


//Interface between Memory and CPU
class Bus {

private:

	Memory& ram;

public:

	Bus(Memory& memInstance);

	uint8_t readByte(uint32_t address);
	uint16_t readHalfWord(uint32_t address);
	uint32_t readWord(uint32_t address);

	void writeByte(uint32_t address, uint8_t value);
	void writeHalfWord(uint32_t address, uint16_t value);
	void writeWord(uint32_t address, uint32_t value);

};