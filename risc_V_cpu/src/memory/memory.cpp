#include "memory.h"
#include "../exception/HardwareException.h"

Memory::Memory() {

	//4 MB memory initialized with 0
	ram.resize(4 * 1024 * 1024, 0);
}

void Memory::reset() {

	std::fill(ram.begin(), ram.end(), 0);
}

uint8_t Memory::readByte(uint32_t address) {

	if (address > 0x3ffff)
		throw MemoryException("Address out of Bound....(in Memory readByte)");

	return ram[address];

}

uint16_t Memory::readHalfWord(uint32_t address) {

	if (address > 0x3ffff) {

		throw MemoryException("Address out of Bound....(in Memory readHalfWord)");
	}


	if (address & 1) {
		//only divisable by 2
		throw MemoryException("Misaligned byte access....(in Memory readHalfWord)");
	}

	return ram[address] | (uint16_t(ram[address + 1]) << 8);
}

//32-bit word
uint32_t Memory::readWord(uint32_t address) {

	if (address > 0x3ffff) {

		throw MemoryException("Address out of Bound....(in Memory readWord)");
	}

	if (address & 3) {
		//only divisable by four
		throw MemoryException("Misaligned byte access....(in Memory readWord)");
	}


	//littleendian style 
	//reading four byte

	return ((uint32_t)ram[address + 3]	<< 24		|
			(uint32_t)ram[address + 2]	<< 16		|
			(uint32_t)ram[address + 1]	<< 8		|
			(uint32_t)ram[address]
		);

}

void Memory::writeByte(uint32_t address, uint8_t value) {

	if (address > 0x3ffff)
		throw MemoryException("Address out of Bound....(in Memory writeByte)");

	ram[address] = value;

}

void Memory::writeHalfWord(uint32_t address, uint16_t value) {

	if (address > 0x3ffff) {

		throw MemoryException("Address out of Bound....(in Memory writeHalfWord)");
	}

	if (address & 1) {
		//only divisable by 2
		throw MemoryException("Misaligned byte access....(in Memory writeHalfWord)");
	}

	ram[address] = uint8_t(value);

	ram[address + 1] = uint8_t(value >> 8);

}

void Memory::writeWord(uint32_t address, uint32_t value) {


	if (address > 0x3ffff) {

		throw MemoryException("Address out of Bound....(in Memory writeWord)");
	}

	if (address & 3) {
		//only divisable by four
		throw MemoryException("Misaligned byte access....(in Memory writeWord)");
	}

	ram[address] = uint8_t(value);

	ram[address + 1] = uint8_t(value >> 8);

	ram[address + 2] = uint8_t(value >> 16);

	ram[address + 3] = uint8_t(value >> 24);

}