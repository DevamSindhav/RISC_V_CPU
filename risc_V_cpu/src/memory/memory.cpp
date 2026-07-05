#include "memory.h"

Memory::Memory() {

	//4 MB memory initialized with 0
	ram.resize(4 * 1024 * 1024, 0);
}

uint8_t Memory::readByte(uint32_t address) {

	return Memory::ram[address];

}

//32-bit word
uint32_t Memory::readWord(uint32_t address) {

	//littleendian style 
	//reading four byte

	return ((uint32_t)ram[address + 3]	<< 24		|
			(uint32_t)ram[address + 2]	<< 16		|
			(uint32_t)ram[address + 1]	<< 8		|
			(uint32_t)ram[address]
		);

}

void Memory::writeByte(uint32_t address, uint8_t value) {

	ram[address] = value;

}

void Memory::writeWord(uint32_t address, uint32_t value) {

	ram[address] = uint8_t(value);

	ram[address + 1] = uint8_t(value >> 8);

	ram[address + 2] = uint8_t(value >> 16);

	ram[address + 3] = uint8_t(value >> 24);

}