
#include "CPU.h"
#include "..\..\system\Syscallhandler.h"
#include <iostream>
#include <iomanip> //for printing in hex
#include <cstdint>

CPU::CPU(Bus& busInstance) : 
	bus(busInstance) {

	isCpuHalted = false; //at boot obviously it should not stop

	//fill all regs with 0;
	registers.fill(0);

	registers[0] = 0x0; // x0 is always 0

	pc = 0x0; // PC restart value;

}

bool CPU::isHalted() const { return isCpuHalted; }

void CPU::printRegisters() {

	std::cout << "---- CPU STATE ----\n";

	std::cout << "PC : 0x"
				<< std::setfill('0') << std::setw(8)
				<< std::hex << pc << "\n\n";

	for (int i = 0; i < 32; i++) {

		std::cout << "x" << std::dec << std::setfill('0') 
					<< std::setw(2) << i << " : 0x"
					<< std::setfill('0') << std::setw(8)
					<< std::hex << registers[i] << "\t";

		if ((i + 1) % 4 == 0) {
			std::cout << "\n";
		}

	}

	std::cout << "-------------------\n";

	std::cout << std::dec;

}

void CPU::step() {

	//1.fetch part -> fetch inst from memory location pointed by pc
	uint32_t inst = bus.readWord(pc);

	DecodedInstruction decInst = decoder.decodeInstruction(inst);


	switch (decInst.opcode) {
		case Opcode::R_TYPE:
			executeR_TYPE(decInst);
			break;

		case Opcode::I_TYPE :
			executeI_TYPE(decInst);
			break;

		case Opcode::LOAD :
			executeLOAD(decInst);
			break;

		case Opcode::STORE :
			executeSTORE(decInst);
			break;

		case Opcode::BRANCH :
			executeBRANCH(decInst);
			break;

		case Opcode::JAL :
			executeJAL(decInst);
			break;
		case Opcode::JALR :
			executeJALR(decInst);
			break;

		case Opcode::LUI :
			executeLUI(decInst);
			break;

		case Opcode::AUIPC :
			executeAUIPC(decInst);
			break;

		case Opcode::SYSTEM:
			executeSYSTEM(decInst);
			break;

		default:
			//custom exception from exception
	} 
	///PC updted in respective methods
}

void CPU::executeR_TYPE(const DecodedInstruction& decInst) {
	
	ALUop operation
		= ALU::getControlSignal(decInst.opcode,
								decInst.funct3,
								decInst.funct7
			);

	uint32_t result 
		= alu.compute(registers[decInst.rs1],
						registers[decInst.rs2],
						operation
			);

	//only write back id rd != 0th register

	if (decInst.rd != 0x0) {
		registers[decInst.rd] = result;
	}

	pc += 4;
}

void CPU::executeI_TYPE(const DecodedInstruction& decInst) {

	ALUop operation
		= ALU::getControlSignal(decInst.opcode,
			decInst.funct3,
			decInst.funct7
		);

	uint32_t result
		= alu.compute(registers[decInst.rs1],
			decInst.imm,
			operation
		);

	//only write back id rd != 0th register

	if (decInst.rd != 0x0) {
		registers[decInst.rd] = result;
	}

	pc += 4;
}

void CPU::executeLOAD(const DecodedInstruction& decInst) {

	//address calculation
	//need to cast immediate field to int32_t to retain its sign
	uint32_t effAdd = alu.compute(registers[decInst.rs1] , decInst.imm, ALUop::ADD);
	uint32_t result;


	switch (decInst.funct3) {

	case 0x0:
		//LB load byte only fist 8 bit with sign
		result = uint32_t(int8_t( bus.readByte(effAdd)));
		break;

	case 0x1:
		//LH load half word 16 bits with sign
		result = uint32_t(int16_t(bus.readHalfWord(effAdd)));
		break;

	case 0x2:
		//LW load worfd whole  word as is
		result = bus.readWord(effAdd);
		break;

	case 0x4:
		//LBU load byte without sign stuff 0s
		result = uint32_t(bus.readByte(effAdd));
		break;

	case 0x5:
		///LHU load half word unsigneed stuff 0s
		result = uint32_t(bus.readHalfWord(effAdd));
		break;
	}

	if (decInst.rd != 0x0) {
		registers[decInst.rd] = result;
	}

	pc += 4;
}

void CPU::executeSTORE(const DecodedInstruction& decInst) {

	//effAdd calculation same as LOAD
	uint32_t effAdd = alu.compute(registers[decInst.rs1], decInst.imm, ALUop::ADD);
	
	switch (decInst.funct3) {
		case 0x0:
			//SB store byte
			bus.writeByte(effAdd, uint8_t(registers[decInst.rs2]));
			break;

		case 0x1:
			//SH store halfword
			bus.writeHalfWord(effAdd, uint16_t(registers[decInst.rs2]));
			break;

		case 0x2:
			bus.writeWord(effAdd, registers[decInst.rs2]);
			break;
	}
	pc += 4;
}

void CPU::executeBRANCH(const DecodedInstruction& decInst) {

	//we haev made sure that decoder returns a sign extended immediate value

	uint32_t branchAdd = alu.compute(pc, decInst.imm, ALUop::ADD);

	// if no condition fulfilled we simply go to next instruction in line
	uint32_t tempPc = pc + 4; 

	uint32_t num1 = registers[decInst.rs1];
	uint32_t num2 = registers[decInst.rs2];

	//now check which branch and update pc accordingly
	switch (decInst.funct3) {

		case 0x0 :
			//BEQ branch if num1 == num2
			if (alu.compute(num1, num2, ALUop::SUB) == 0x0)
				tempPc = branchAdd;
			break;

		case 0x1 :
			//BNE branch if num1 != num2
			if (alu.compute(num1, num2, ALUop::SUB) != 0x0)
				tempPc = branchAdd;
			break;

		case 0x4 :
			//BLT branch if num1 < num2 signed
			if (alu.compute(num1, num2, ALUop::SLT))
				tempPc = branchAdd;
			break;

		case 0x5 :
			//BGE branch if num1 >= num2 signed
			if (!alu.compute(num1, num2, ALUop::SLT))
				tempPc = branchAdd;
			break;

		case 0x6 :
			//BLTU branch if num1 < num2 unsigned
			if (alu.compute(num1, num2, ALUop::SLTU))
				tempPc = branchAdd;
			break;

		case 0x7:
			//BGEU branch if num1 >= num2 unsigned
			if (!alu.compute(num1, num2, ALUop::SLTU))
				tempPc = branchAdd;
			break;
	}

	pc = tempPc;

} 

void CPU::executeJAL(const DecodedInstruction& decInst) {
	//JAL an uncoditional jump with return address
	//save the return address
	//the return address is pc + 4 i.e. nect inst in sequence
	// Only save the return address if the destination isn't x0
	if(decInst.rd != 0x0)
		registers[decInst.rd] = pc + 4;

	//now we calculate the jump address and update the pc

	pc = alu.compute(pc, decInst.imm, ALUop::ADD);

} 

void CPU::executeJALR(const DecodedInstruction& decInst) {

	//JALR is used when we want to jump to a location
	//which is calculated using index registers

	//Link step or return address storage
	if (decInst.rd != 0x0)
		registers[decInst.rd] = pc + 4;

	//Now the jum step
	//calculate the jump Address
	//mask last bit to zero

	pc = alu.compute(registers[decInst.rs1], decInst.imm, ALUop::ADD) & ~1;

} 

void CPU::executeLUI(const DecodedInstruction& decInst) {

	//LUI load upper immediate

	if (decInst.rd != 0x0)
		registers[decInst.rd] = decInst.imm;

	pc += 4; //next inst.
}

void CPU::executeAUIPC(const DecodedInstruction& decInst) {

	//AUIPC add upper immediate to PC

	if (decInst.rd != 0x0)
		registers[decInst.rd] = alu.compute(pc, decInst.imm, ALUop::ADD);

	pc += 4; //next inst.
} 

void CPU::executeSYSTEM(const DecodedInstruction& decInst) {

	//two SYSTEM instructions ECALL and EBREAK

	if (decInst.imm == 0x0)
		//ECALL means immediate == 0
		SysCallHandler::handleECALL(registers, isCpuHalted);

	else if (decInst.imm == 0x1)
		//EBREAK means immediate == 1
		SysCallHandler::handleEBREAK(registers, pc);

	pc += 4;
}
