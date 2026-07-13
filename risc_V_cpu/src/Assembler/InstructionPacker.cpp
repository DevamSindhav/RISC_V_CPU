#include "InstructionPacker.h"

uint32_t InstructionPacker::packInstruction(DecodedInstruction& decInst , InstructionType intType) {

	uint32_t macInst = 0x0;

	switch (intType) {

		case InstructionType::R: 
			macInst = InstructionPacker::packRtype(decInst);
			break;

		case InstructionType::I:
			macInst = InstructionPacker::packItype(decInst);
			break;

		// to specifically distinguish the SRAI AND SRLI 
		case InstructionType::I_SHIFT:
			macInst = InstructionPacker::packI_SHIFT_type(decInst);
			break;

		case InstructionType::S:
			macInst = InstructionPacker::packStype(decInst);
			break;

		case InstructionType::B:
			macInst = InstructionPacker::packBtype(decInst);
			break;

		case InstructionType::U:
			macInst = InstructionPacker::packUtype(decInst);
			break;

		case InstructionType::J:
			macInst = InstructionPacker::packJtype(decInst);
			break;

		case InstructionType::SYSTEM:
			macInst = InstructionPacker::packSYSTEM(decInst);
			break;

	}


	return macInst;
}

uint32_t InstructionPacker::packRtype(DecodedInstruction& decInst){
	return uint32_t(decInst.opcode) |
		(decInst.rd << 7) |
		(decInst.funct3 << 12) |
		(decInst.rs1 << 15) |
		(decInst.rs2 << 20) |
		(decInst.funct7 << 25);
}

uint32_t InstructionPacker::packItype(DecodedInstruction& decInst){
	return uint32_t(decInst.opcode) |
		(decInst.rd << 7) |
		(decInst.funct3 << 12) |
		(decInst.rs1 << 15) |
		((decInst.imm & 0xFFF) << 20);  // Mask to 12 bits
}

uint32_t InstructionPacker::packStype(DecodedInstruction& decInst) {
	return uint32_t(decInst.opcode) |
		((decInst.imm & 0x1f) << 7) |
		(decInst.funct3 << 12) |
		(decInst.rs1 << 15) |
		(decInst.rs2 << 20) |
		(((decInst.imm >> 5) & 0x7f) << 25);
}

uint32_t InstructionPacker::packBtype(DecodedInstruction& decInst) {
	
	return uint32_t(decInst.opcode) |
		(((decInst.imm >> 11) & 0x1) << 7) |
		(((decInst.imm >> 1) & 0xf) << 8) |
		(decInst.funct3 << 12) |
		(decInst.rs1 << 15) |
		(decInst.rs2 << 20) |
		(((decInst.imm >> 5) & 0x3f) << 25) |
		(((decInst.imm >> 12) & 0x1) << 31);

}

uint32_t InstructionPacker::packUtype(DecodedInstruction& decInst) {
	
	return uint32_t(decInst.opcode) |
		(decInst.rd << 7) |
		((decInst.imm & 0xFFFFF) << 12); // Mask to 20 bits and shift to top

}

uint32_t InstructionPacker::packJtype(DecodedInstruction& decInst) {
	
	return uint32_t(decInst.opcode) |
		(decInst.rd << 7) |
		(((decInst.imm >> 12) & 0xff) << 12) |
		(((decInst.imm >> 11) & 0x1) << 20) |
		(((decInst.imm >> 1) & 0x3ff) << 21) |
		(((decInst.imm >> 20) & 0x1) << 31);
}

uint32_t InstructionPacker::packSYSTEM(DecodedInstruction& decInst) {

	return uint32_t(decInst.opcode) |
		(decInst.funct7 << 20);
}

uint32_t InstructionPacker::packI_SHIFT_type(DecodedInstruction& decInst) {
	return static_cast<uint32_t>(decInst.opcode) |
		(decInst.rd << 7) |
		(decInst.funct3 << 12) |
		(decInst.rs1 << 15) |
		((decInst.imm & 0x1F) << 20) |  // Only the bottom 5 bits of the immediate
		(decInst.funct7 << 25);         // Safely drop in the 0x20 or 0x00
}