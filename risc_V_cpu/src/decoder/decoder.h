#pragma once
#include <cstdint>
#include "../ISA/instructions.h"
#include "../ISA/decodedinstruction.h"

class Decoder {

public:

	Decoder();

	//decoding logic
	DecodedInstruction decodeInstruction(uint32_t inst);
};
