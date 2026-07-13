#include "ALU.h"
#include "../../exception/HardwareException.h"
#include <cstdint>


ALU::ALU(){}

uint32_t ALU::compute(uint32_t operandA, uint32_t operandB, ALUop operation) {

	switch (operation) {

		case ALUop::ADD :
			return operandA + operandB;

		case ALUop::SUB :
			return operandA - operandB;

		case ALUop::SLL :
			return operandA << (operandB & 0x1f);

		case ALUop::SRL :
			return operandA >> (operandB & 0x1f);

		case ALUop::SRA :
			//for a arithmetic shift we need this
			return static_cast<uint32_t>(static_cast<int32_t>(operandA) >> (operandB & 0x1f));

		case ALUop::XOR :
			return operandA ^ operandB;

		case ALUop::OR :
			return operandA | operandB;

		case ALUop::AND :
			return operandA & operandB;

		case ALUop::SLT :
			return int32_t(operandA) < int32_t(operandB) ? 1 : 0;

		case ALUop::SLTU :
			return operandA < operandB ? 1 : 0;

		default:
			throw DecoderException("Invalid Operation... (in ALU compute)");
	}
	return 0x0;
}

ALUop ALU::getControlSignal(Opcode opcode, uint32_t funct3, uint32_t funct7) {

	switch (opcode) {

		case Opcode::R_TYPE :

			if (funct3 == 0x0 && funct7 == 0x0) return ALUop::ADD;
			if (funct3 == 0x0 && funct7 == 0x20) return ALUop::SUB;
			if (funct3 == 0x1 && funct7 == 0x0) return ALUop::SLL;
			if (funct3 == 0x2 && funct7 == 0x0) return ALUop::SLT;
			if (funct3 == 0x3 && funct7 == 0x0) return ALUop::SLTU;
			if (funct3 == 0x4 && funct7 == 0x0) return ALUop::XOR;
			if (funct3 == 0x5 && funct7 == 0x0) return ALUop::SRL;
			if (funct3 == 0x5 && funct7 == 0x20) return ALUop::SRA;
			if (funct3 == 0x6 && funct7 == 0x0) return ALUop::OR;
			if (funct3 == 0x7 && funct7 == 0x0) return ALUop::AND;
			break;

		case Opcode::I_TYPE:

			if (funct3 == 0x0) return ALUop::ADD;
			if (funct3 == 0x1 && funct7 == 0x0) return ALUop::SLL;
			if (funct3 == 0x2) return ALUop::SLT;
			if (funct3 == 0x3) return ALUop::SLTU;
			if (funct3 == 0x4) return ALUop::XOR;
			if (funct3 == 0x5 && funct7 == 0x0) return ALUop::SRL;
			if (funct3 == 0x5 && funct7 == 0x20) return ALUop::SRA;
			if (funct3 == 0x6) return ALUop::OR;
			if (funct3 == 0x7) return ALUop::AND;
			break;

		default :
			throw DecoderException("Invalid Operation... (in ALU getControlSignal)");

	}

	return ALUop::ADD;
}