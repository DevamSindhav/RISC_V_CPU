#pragma once

#include <cstdint>

enum ALUop {

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

	void compute(uint32_t source1, uint32_t source2, ALUop operation);

};