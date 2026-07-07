#pragma once
#include <cstdint>
#include "instructions.h"

struct DecodedInstruction{

	Opcode opcode;
	uint32_t rd;
	uint32_t rs1;
	uint32_t rs2;
	uint32_t funct3;
	uint32_t funct7;
	int32_t imm; // a signed number
};
