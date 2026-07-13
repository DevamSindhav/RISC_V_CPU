
#include "memory/memory.h"
#include "bus/bus.h"
#include "core/CPU/CPU.h"
#include "loader/Loader.h"
#include "exception/HardwareException.h"
#include "exception/AssemblerException.h"

#include "Assembler/Assembler.h"

#include<iostream>
#include <fstream>


int main() {
	std::cout << "Booting RISC-V Simulator....\n";

	//initialize memory
	//Memory ram;

	//connect bus to memory
	//Bus bus(ram);

	//connect bus to CPU
	//CPU cpu(bus);

	//std::cout << "Hardware initialized Successfully!\n";

	//cpu.printRegisters();

	//std::string filePath;

	//std::cout << "Enter file path to execute (.asm) : ";
	//std::cin >> filePath;
	//try {

	//	std::string outPath = Assembler::assemble(filePath);

	//	Loader::loadProgram(bus, outPath);

	//	while (!cpu.isHalted()) {
	//		cpu.step();
	//	}

	//	std::cout << "\nProgram executed successfully!!\n";

	//	cpu.printRegisters();
	//}
	//catch (const AssemblerException& ae) {
	//	std::cout << ae.what() << std::endl;

	//	std::cout << "\nCPU execution stopped due to an error.....\n";

	//	cpu.printRegisters();
	//}
	//catch (const HardwareException& he) {
	//	std::cout << he.what() << std::endl;

	//	std::cout << "\nCPU execution stopped due to an error.....\n";

	//	cpu.printRegisters();
	//}
	//catch (const std::runtime_error& re) {
	//	std::cout << re.what() << std::endl;

	//	std::cout << "\nCPU execution stopped due to interanl an error.....\n";

	//	cpu.printRegisters();
	//}

	//automatic Testing loops
	
	//File that contains name of all the files to be tested 
	std::string files = "C:/Users/ASUS/OneDrive/Desktop/Risc_V_CPU/risc_V_cpu/risc_V_cpu/src/TEST/programs.txt";

	std::ifstream inFile(files);

	std::string filePath;

	int testsPassed = 0;
	int totalTests = 0;

	while (std::getline(inFile, filePath)) {

		if (filePath.empty()) continue;

		totalTests++;
		std::cout << "Running: " << filePath << "...\n";

		Memory ram;

		Bus bus(ram);

		CPU cpu(bus);
		try {

			std::string outPath = Assembler::assemble(filePath);

			Loader::loadProgram(bus, outPath);

			while (!cpu.isHalted()) {
				cpu.step();
			}

			std::cout << "\nProgram executed successfully!!\n";

			if (cpu.getRegister(31) == 1) {
				std::cout << "--> [PASS]\n";
				testsPassed++;
			}
			else {
				std::cout << "--> [FAIL] x31 was not 1!\n";
				break;
			}
			
		}
		catch (const AssemblerException& ae) {
			std::cout << "--> [ASSEMBLER CRASH] " << ae.what() << "\n";
		}
		catch (const HardwareException& he) {
			std::cout << "--> [HARDWARE CRASH] " << he.what() << "\n";

			std::cout << "\nCPU execution stopped due to an error.....\n";

			cpu.printRegisters();
		}
		catch (const std::runtime_error& re) {
			std::cout << "--> [INTERNAL CRASH] " << re.what() << "\n";

			std::cout << "\nCPU execution stopped due to interanl an error.....\n";

			cpu.printRegisters();
		}

	}

	std::cout << "\n====================================\n";
	std::cout << "Test Suite Complete: " << testsPassed << " / " << totalTests << " passed.\n";
	std::cout << "====================================\n";

	return 0;
}