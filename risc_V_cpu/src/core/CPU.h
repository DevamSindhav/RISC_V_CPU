#pragma once

#include "..\bus\bus.h"

#include <cstdint> //for uint32_t
#include <array>

class CPU {

private :

	std::array<uint32_t, 32> registers; // 32 registers of 32 bits each

	uint32_t pc; // program counter

	//Bus connection
	Bus& bus;

public :

	CPU(Bus& busInstance);

	//helper method to print CPU registers
	void printRegisters();

};
