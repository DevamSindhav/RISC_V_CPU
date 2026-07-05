#pragma once

#include "..\..\bus\bus.h"
#include "..\..\ISA\decodedinstruction.h"
#include "..\..\decoder\decoder.h"

#include <cstdint> //for uint32_t
#include <array>

class CPU {

private :

	std::array<uint32_t, 32> registers; // 32 registers of 32 bits each

	uint32_t pc; // program counter

	//Bus connection
	Bus& bus;

	//Decoder connection
	Decoder& decoder;

public :

	CPU(Bus& busInstance , Decoder& decoder);

	//helper method to print CPU registers
	void printRegisters();

	//step function or an instruction cycle?
	void step();

	//all the type of inst execution func
	void executrR_TYPR(DecodedInstruction decInst);
	void executrI_TYPR(DecodedInstruction decInst);
	void executrLOAD(DecodedInstruction decInst);
	void executrSTORE(DecodedInstruction decInst);
	void executrBRANCH(DecodedInstruction decInst);
	void executrJAL(DecodedInstruction decInst);
	void executrJALR(DecodedInstruction decInst);
	void executrLUI(DecodedInstruction decInst);
	void executrAUIPC(DecodedInstruction decInst);

};
