#pragma once
#include "../../ISA/instructions.h"
#include <cstdint>
//enum class forces scoped access
enum class ALUop {

	ADD,
	SUB,
	SLL, //shift left logical
	SRL, //shift right logical
	SRA, //shift right Arithmetic
	XOR,
	OR,
	AND,
	SLT, //set less than signed
	SLTU //set less than unsigned

};

class ALU {

public:

	ALU();

	uint32_t compute(uint32_t operandA, uint32_t operandB , ALUop operation);

	//for decoding the ALUop from opecode , funct3 and funct7
	static ALUop getControlSignal(Opcode opcode, uint32_t funct3, uint32_t funct7);
};