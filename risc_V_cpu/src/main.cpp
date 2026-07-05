
#include "memory/memory.h"
#include "bus/bus.h"
#include "core/CPU/CPU.h"

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

	cpu.printRegisters();

	return 0;
}