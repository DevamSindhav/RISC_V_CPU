#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
#include "../ISA/instructions.h"

enum class InstructionType{
	R ,
	I ,
	S ,
	B ,
	U ,
	J ,
	SYSTEM
};

struct InstructionMetadata {

	InstructionType instTy;
	Opcode opcode;
	uint32_t funct3;
	uint32_t funct7;
	int expectedOperands;

};

//kinda hardcoding them so inline is ok, i guess?
inline const std::unordered_map<std::string, InstructionMetadata> INSTRUCTION_TABLE = {

	//R-TYPE
	{"ADD" , {InstructionType::R ,Opcode::R_TYPE,0x00 , 0x00 , 3}},
	{"SUB" , {InstructionType::R ,Opcode::R_TYPE,0x00,0x20 , 3}},
	{"SLL" , {InstructionType::R ,Opcode::R_TYPE,0x01 ,0x00 , 3}},
	{"SLT" , {InstructionType::R ,Opcode::R_TYPE,0x02 ,0x00 , 3}},
	{"SLTU" , {InstructionType::R ,Opcode::R_TYPE, 0x03,0x00 , 3 }},
	{"XOR" , {InstructionType::R ,Opcode::R_TYPE,0x04 ,0x00 , 3}},
	{"SRL" , {InstructionType::R ,Opcode::R_TYPE, 0x05,0x00 , 3}},
	{"SRA" , {InstructionType::R ,Opcode::R_TYPE,0x05 ,0x20 , 3}},
	{"OR" , {InstructionType::R ,Opcode::R_TYPE,0x06 ,0x00 , 3}},
	{"AND" , {InstructionType::R ,Opcode::R_TYPE,0x07,0x00 , 3}},

	//I-TYPE
	{"ADDI" , {InstructionType::I , Opcode::I_TYPE,0x00,0x00 , 3}},
	{"SLTI" , {InstructionType::I , Opcode::I_TYPE,0x02,0x00 , 3}},
	{"SLTIU" , {InstructionType::I ,Opcode::I_TYPE,0x03,0x00 , 3 }},
	{"XORI" , {InstructionType::I ,Opcode::I_TYPE,0x04 ,0x00 , 3}},
	{"ORI" , {InstructionType::I , Opcode::I_TYPE,0x06,0x00 , 3}},
	{"ANDI" , {InstructionType::I ,Opcode::I_TYPE,0x07 ,0x00 , 3}},
	{"SLLI" , {InstructionType::I ,Opcode::I_TYPE,0x01,0x00 , 3 }},
	{"SRLI" , {InstructionType::I ,Opcode::I_TYPE,0x05,0x00 , 3 }},
	{"SRAI" , {InstructionType::I ,Opcode::I_TYPE,0x05 ,0x20 , 3}},


	//LOAD but I-TYPE
	{"LB" , {InstructionType::I , Opcode::LOAD,0x00, 0x00, 3 }},
	{"LH" , {InstructionType::I ,Opcode::LOAD,0x01, 0x00, 3 }},
	{"LW" , {InstructionType::I , Opcode::LOAD,0x02, 0x00, 3}},
	{"LBU" , {InstructionType::I ,Opcode::LOAD,0x04, 0x00, 3 }},
	{"LHU" , {InstructionType::I , Opcode::LOAD,0x05, 0x00, 3}},


	{"JALR" , {InstructionType::I ,Opcode::JALR ,0x00, 0x00, 3 }},


	//S-TYPE
	{"SB" , {InstructionType::S ,Opcode::STORE,0x00, 0x00, 3}},
	{"SH" , {InstructionType::S , Opcode::STORE,0x01, 0x00, 3}},
	{"SW" , {InstructionType::S , Opcode::STORE,0x02, 0x00, 3}},

	//B-TYPE
	{"BEQ" , {InstructionType::B , Opcode::BRANCH  ,0x00, 0x00, 3}},
	{"BNE" , {InstructionType::B , Opcode::BRANCH ,0x01, 0x00, 3 }},
	{"BLT" , {InstructionType::B , Opcode::BRANCH ,0x04, 0x00, 3 }},
	{"BGE" , {InstructionType::B , Opcode::BRANCH ,0x05, 0x00, 3 }},
	{"BLTU" , {InstructionType::B , Opcode::BRANCH,0x06, 0x00, 3 }},
	{"BGEU" , {InstructionType::B , Opcode::BRANCH,0x07, 0x00, 3 }},

	//U-TYPE
	{"LUI" , {InstructionType::U ,Opcode::LUI,0x00, 0x00, 2 }},
	{"AUIPC" , {InstructionType::U ,Opcode::AUIPC,0x00, 0x00, 2 }},

	//J-TYPE
	{"JAL" , {InstructionType::J ,Opcode::JAL,0x00, 0x00, 2 }},

	//SYSTEM
	{"ECALL" , {InstructionType::SYSTEM ,Opcode::SYSTEM , 0x0, 0x000, 0}},
	{"EBREAK" , {InstructionType::SYSTEM ,Opcode::SYSTEM ,0x0, 0x001, 0 }}

};
