#include "Syscallhandler.h"
#include<iomanip>

SysCallHandler::SysCallHandler(){}

void SysCallHandler::handleECALL(std::array<uint32_t, 32>& registers, bool& isCpuHalted) {

	//register x17 contains the sysCall
	//we decide which system call based in the content of registerx17
	switch (registers[17]) {

		case 1:
			//Print the Integer int in the x10 register
			std::cout << int32_t(registers[10]) << std::endl;
			break;

		case 10:
			//exit the program
			isCpuHalted = true; //halt the CPU i.e. stop the loop
			break;

		default:
			std::cout << "Invalid System call....";
			break;
	}

}

void SysCallHandler::handleEBREAK(std::array<uint32_t, 32>& registers, uint32_t pc) {
	
	std::cout << "\n--- [DEBUG] EBREAK HIT AT PC: 0x" << std::hex << pc << " ---\n";

	std::cout << "\n---- CPU STATE ----\n";

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

	std::cout << "\nPress any button to exit Debugging mode....";
	char temp;
	std::cin >> temp;
}