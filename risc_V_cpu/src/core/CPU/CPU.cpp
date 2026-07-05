
#include "CPU.h"
#include <iostream>
#include <iomanip> //for printing in hex
#include <cstdint>

CPU::CPU(Bus& busInstance , Decoder& decoderInstance) : 
	bus(busInstance) , decoder(decoderInstance){

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

void CPU::step() {

	//1.fetch part -> fetch inst from memory location pointed by pc
	uint32_t inst = bus.readWord(pc);

	DecodedInstruction decInst = decoder.decodeInstruction(inst);


	switch (decInst.opcode) {
		case Opcode::R_TYPE:
			executeR_TYPE(decInst);
			break;

		case Opcode::I_TYPE :
			executeI_TYPE(decInst)
			break;

		case Opcode::LOAD :
			executeLOAD(decInst);
			break;

		case Opcode::STORE :
			executeSTORE(decInst);
			break;

		case Opcode::BRANCH :
			executeBRANCH(decInst);
			break;

		case Opcode::JAL :
			executeJAL(decInst);
			break;
		case Opcode::JALR :
			executeJALR(decInst);
			break;

		case Opcode::LUI :
			executeLUI(decInst);
			break;

		case Opcode::AUIPC :
			executeAUIPC(decInst);
			break;

		default:
			//custom exception from exception
	} 
	///PC updted in respective methods
}

