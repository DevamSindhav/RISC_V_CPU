#include "decoder.h"
#include "../exception/HardwareException.h"

#include <cstdint>

Decoder::Decoder(){}

DecodedInstruction Decoder::decodeInstruction(uint32_t inst) {

	DecodedInstruction decInst;

	decInst.opcode	= static_cast<Opcode>(inst & 0x7f); //0-6  opcode
	decInst.rd = (inst >> 7) & 0x1f; //7-11 rd
	decInst.funct3 = (inst >> 12) & 0x7; // 12-14 funct3
	decInst.rs1 = (inst >> 15) & 0x1f; // 15-19 rs1
	decInst.rs2 = (inst >> 20) & 0x1f; // 20-24 rs2
	decInst.funct7 = (inst >> 25) & 0x7f; //25-31 funct7

	//the decoder seperates the bits such that they are always
	//in the format that is required
	//no headache of conversion in other modules
	switch (decInst.opcode) {

		case Opcode::R_TYPE :
			decInst.imm = 0x0;
			break;

		case Opcode::I_TYPE :
		case Opcode::LOAD	:
		case Opcode::JALR	:
			decInst.imm = ((int32_t)inst >> 20);
			break;

		case Opcode::STORE :
			decInst.imm = ((int32_t)(inst & 0xFE000000) >> 20) | 
							((inst >> 7) & 0x1f);
			break;

		case Opcode::BRANCH :
			
			decInst.imm = ((int32_t)(inst & 0x80000000) >> 19) |
							((inst & 0x00000080) << 4) |
							((inst & 0x00000f00) >> 7) |
							((inst & 0x7f000000) >> 20);
			break;

		case Opcode::JAL :
			
			decInst.imm = ((int32_t)(inst & 0x80000000) >> 11) |
							(inst & 0x000FF000) |
							((inst & 0x7FE00000) >> 20) |
							((inst & 0x00100000) >> 9);
			break;

		case Opcode::LUI   :
		case Opcode::AUIPC :
			decInst.imm = inst & 0xfffff000;
			break;
		
		default :
			throw DecoderException("Invalid Instruction... (in Decoder decodeInstruction)");

	}

	return decInst;
}
