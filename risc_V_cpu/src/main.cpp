
#include "memory/memory.h"
#include "bus/bus.h"
#include "core/CPU/CPU.h"
#include "loader/Loader.h"
#include "exception/HardwareException.h"

#include<iostream>


int main() {
	std::cout << "Booting RISC-V Simulator....\n";

	//initialize memory
	Memory ram;

	//connect bus to memory
	Bus bus(ram);

	//connect bus to CPU
	CPU cpu(bus);

	std::cout << "Hardware initialized Successfully!\n";

	//cpu.printRegisters();

	std::string filePath;

	std::cout << "Enter file path to execute (.hex) : ";
	std::cin >> filePath;
	try {
		Loader::loadProgram(bus, filePath);

		while (!cpu.isHalted()) {
			cpu.step();
		}

		std::cout << "\nProgram executed successfully!!\n";

		cpu.printRegisters();
	}
	catch (const HardwareException& he) {
		std::cout << he.what() << std::endl;

		std::cout << "\nCPU execution stopped due to an error.....\n";

		cpu.printRegisters();
	}
	catch (const std::runtime_error& re) {
		std::cout << re.what() << std::endl;

		std::cout << "\nCPU execution stopped due to interanl an error.....\n";

		cpu.printRegisters();
	}

	return 0;
}