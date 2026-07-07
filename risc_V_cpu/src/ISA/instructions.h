#pragma once
#include <cstdint>

//opcode wirings 
//decodeing solely on opcode
//means all which can not be decoded by opcode are addressedd as same
//the inst which are not distingushable from opcode will be further decode
//based on fields like funct3 and etc...
enum class Opcode : uint32_t {

	R_TYPE = 0x33,
	I_TYPE = 0x13,
	LOAD = 0x03,
	STORE = 0x23,
	BRANCH = 0x63,
	JAL = 0x6F,
	JALR = 0x67,
	LUI = 0x37,
	AUIPC = 0x17,
	SYSTEM = 0x73
};