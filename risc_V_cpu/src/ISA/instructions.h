#pragma once
#include <cstdint>

//opcode wirings 
//decodeing solely on opcode
//means all which can not be decoded by opcode are addressedd as same
//the inst which are not distingushable from opcode will be further decode
//based on fields like funct3 and etc...
namespace Opcode {

	const uint32_t R_TYPE	= 0x33;
	const uint32_t I_TYPE	= 0x13;
	const uint32_t LOAD		= 0x03;
	const uint32_t STORE	= 0x23;
	const uint32_t BRANCH	= 0x63;
	const uint32_t JAL		= 0x6F;
	const uint32_t JALR		= 0x67;
	const uint32_t LUI		= 0x37;
	const uint32_t AUIPC	= 0x17;
	const uint32_t SYSTEM	= 0x73;
}