#pragma once

#include <cstdint>
#include <vector>
#include <cmath>

class Memory {

private :
	// memory 
	// //byte addressable 
	// //heap memory used using vector
	std::vector<uint8_t> ram;  

public :

	Memory();

	//read funcs
	uint8_t readByte(uint32_t address);

	uint32_t readWord(uint32_t address);

	//write funcs
	void writeByte(uint32_t address , uint8_t value);

	void writeWord(uint32_t address , uint32_t value);

};

