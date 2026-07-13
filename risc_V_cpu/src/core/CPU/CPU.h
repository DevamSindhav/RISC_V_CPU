#pragma once

#include "../../bus/bus.h"
#include "../../ISA/decodedinstruction.h"
#include "../../decoder/decoder.h"
#include "../ALU/ALU.h"

#include <cstdint> //for uint32_t
#include <array>

class CPU {

private :
	//-------Parts inside CPU-------//

	std::array<uint32_t, 32> registers; // 32 registers of 32 bits each

	uint32_t pc; // program counter

	//to keep track of the program 
	// i.e. to exit the program execution loop
	bool isCpuHalted;

	//Decoder connection
	Decoder decoder;

	//ALU connection
	ALU alu;

	//------Parts outside CPU------//

	//Bus connection wg=hich comes fromm outside
	Bus& bus;

public :

	CPU(Bus& busInstance);

	bool isHalted() const;

	void reset();

	//helper method to print CPU registers
	void printRegisters();

	//step function or an instruction cycle?
	void step();

	//all the type of inst execution func
	void executeR_TYPE(const DecodedInstruction& decInst);
	void executeI_TYPE(const DecodedInstruction& decInst);
	void executeLOAD(const DecodedInstruction& decInst);
	void executeSTORE(const DecodedInstruction& decInst);
	void executeBRANCH(const DecodedInstruction& decInst);
	void executeJAL(const DecodedInstruction& decInst);
	void executeJALR(const DecodedInstruction& decInst);
	void executeLUI(const DecodedInstruction& decInst);
	void executeAUIPC(const DecodedInstruction& decInst);
	void executeSYSTEM(const DecodedInstruction& decInst);

};
