#pragma once

#include "InstructionTable.h"
#include "../ISA/decodedinstruction.h"
#include <cstdint>
#include <vector>

//here decodedInstruction is used with the purpose of the 
//intermediate datatransfer object to make a clean architecture
namespace InstructionPacker {

	uint32_t packRtype(DecodedInstruction& decInst);
	uint32_t packItype(DecodedInstruction& decInst);
	uint32_t packStype(DecodedInstruction& decInst);
	uint32_t packBtype(DecodedInstruction& decInst);
	uint32_t packUtype(DecodedInstruction& decInst);
	uint32_t packJtype(DecodedInstruction& decInst);
	uint32_t packSYSTEM(DecodedInstruction& decInst);

	uint32_t packInstruction(DecodedInstruction& decInst , InstructionType intType);

};