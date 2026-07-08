#include "Loader.h"

#include <cstdint>
#include <iostream>
#include <fstream>

void Loader::loadProgram(Bus& bus, const std::string& filePath) {

	uint32_t currAdd = 0x0; //to point to the address to be written

	std::ifstream is(filePath);

	if (!is.is_open()) {
		throw std::runtime_error("File not opened....( in Loader loadProgram)");
	}

	//read from file and write in memory to current address
	std::string inst;
	while (std::getline(is , inst)) {
		//safety check
		if (inst.empty() || inst == "\r")
			continue;

		//parse string as a base 16 number
		uint32_t instWord = std::stoul(inst,nullptr , 16);

		//write data in mem
		bus.writeWord(currAdd, instWord);

		//inc the pointer
		currAdd += 4;

	}

}