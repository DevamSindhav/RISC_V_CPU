
#include "CPU.h"
#include <iostream>
#include <iomanip> //for printing in hex

CPU::CPU(Bus& busInstance) : bus(busInstance){

	//fill all regs with 0;
	registers.fill(0);

	registers[0] = 0x0; // x0 is always 0

	pc = 0x0; // PC restart value;

}

void CPU::printRegisters() {

	std::cout << "---- CPU STATE ----\n";

	std::cout << "PC : 0x"
				<< std::setfill('0') << std::setw(8)
				<< std::hex << pc << "\n\n";

	for (int i = 0; i < 32; i++) {

		std::cout << "x" << std::dec << std::setfill('0') 
					<< std::setw(2) << i << " : 0x"
					<< std::setfill('0') << std::setw(8)
					<< std::hex << registers[i] << "\t";

		if ((i + 1) % 4 == 0) {
			std::cout << "\n";
		}

	}

	std::cout << "-------------------\n";

	std::cout << std::dec;

}

