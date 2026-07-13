#include "Assembler.h"
#include "InstructionTable.h"
#include "InstructionPacker.h"
#include "../exception/AssemblerException.h"
#include "../ISA/decodedinstruction.h"

#include <algorithm>
#include <sstream>
#include <cctype>
#include <fstream>
#include <filesystem> //for file path parsings
#include <iomanip>

std::string Assembler::assemble(const std::string& filePath) {

	std::unordered_map<std::string, std::uint32_t>symbolTable
		= Assembler::firstPass(filePath);

	return Assembler::secondPass(filePath, symbolTable);
}

std::vector<std::string> Assembler::tokenize(std::string& line) {

	//parsing 
	std::vector<std::string> tokens;

	//remove comments
	size_t commentPos = line.find_first_of("#;");

	if (commentPos != std::string::npos) {
		line = line.substr(0, commentPos);
	}

	//for ease of parsing 
	//replace ',' with ' '
	std::replace(line.begin(), line.end(), ',', ' ');

	//for the S type instruction eg. written as {SW x5, 12(x1)}
	std::replace(line.begin(), line.end(), '(', ' ');
	std::replace(line.begin(), line.end(), ')', ' ');


	//make tokens vector
	std::stringstream ss(line);
	std::string word;
	while (ss >> word) {
		tokens.push_back(word);
	}


	//mnemonics in upper
	if (!tokens.empty()) {
		int mnemonicIndex = 0;

		// If the first word ends with ':', it's a label!
		// Therefore, the mnemonic is the NEXT word.
		if (tokens[0].back() == ':') {
			mnemonicIndex = 1;
		}

		// Uppercase whichever word is the mnemonic
		if (mnemonicIndex < tokens.size()) {
			for (char& c : tokens[mnemonicIndex]) {
				c = std::toupper(c);
			}
		}
	}

	return tokens;
}

uint32_t Assembler::parseRegister(const std::string& regStr, int lineNum) {

	//parse x12 to 12 integer and return uint32_t

	//check if written as x12

	if (regStr.empty() || regStr[0] != 'x') {
		throw OperandException("Invalid Register format....(in Assembler parseRegister).", lineNum);
	}

	int regNum = 0;
	//parse the string to int
	try {
		//exclude x from the string to parse
		regNum = std::stoi(regStr.substr(1));
	}
	catch (...) {
		throw InvalidRegisterException("Invalid register number....(in Assembler parseRegister).", lineNum);
	}

	//check the register bound
	if (regNum < 0 || regNum > 31) {
		throw InvalidRegisterException("Register out of bounds (0-31)....(in Assembler parseRegister).", lineNum);
	}
	
	//directly parsed to uint32_t
	return regNum;
}

int32_t Assembler::parseImmediate(const std::string& token, uint32_t currAddress,
	const std::unordered_map<std::string, uint32_t>& symbolTable, int lineNum) {

	//to parse the immediate from the line
	//we pass the token which contains immediate to this func we get int32_t in return

	 // 1. Is it a Label?
	if (symbolTable.find(token) != symbolTable.end()) {
		// Calculate the PC-relative offset!
		return symbolTable.at(token) - currAddress;
	}

	// 2. Not a label. Try to parse it as a number
	try {
		// Base 0 allows it to automatically detect hex (0x...) or decimal
		return std::stoi(token, nullptr, 0);
	}
	catch (...) {
		throw SymbolNotFoundException("Unknown label or invalid number....(in Assembler parseImmediate) ", lineNum);
	}


}

std::unordered_map<std::string, std::uint32_t> Assembler::firstPass(const std::string& filePath) {

	std::unordered_map<std::string, std::uint32_t>symbolTable;

	std::ifstream inFile(filePath);
	std::string line;

	if (!inFile.is_open()) {
		throw std::runtime_error("File not opened....(in Assembler fisrtPass)");
	}

	int lineNum = 0;

	uint32_t currAddress = 0x0;

	while (std::getline(inFile, line)) {

		lineNum++;

		std::vector<std::string> tokens = tokenize(line);

		if (tokens.empty()) {
			continue;
		}

		//if label
		if (tokens[0].back() == ':') {

			std::string label = tokens[0].substr(0, tokens[0].size() - 1);

			//if label exists
			if (symbolTable.find(label) != symbolTable.end()) {
				throw AssemblerException("Duplicate Defination of label : " + label + "  (in Assembler firstPass)", lineNum);
			}

			symbolTable[label] = currAddress;

			if (tokens.size() == 1) {
				continue;
			}
		}
		//next line all inst of 4 byte
		currAddress += 4;
	}
	inFile.close();
	return symbolTable;
}

std::string Assembler::secondPass(const std::string& filePath, std::unordered_map<std::string, uint32_t>& symbolTable) {

	std::string line;

	std::filesystem::path p(filePath);

	p.replace_extension(".hex");
	std::string outPath = p.string();

	std::ifstream inFile(filePath);
	std::ofstream outFile(outPath);

	if (!inFile.is_open()) {
			throw std::runtime_error("Could not open input file for Pass 2");
		}
	if (!outFile.is_open()) {
		throw std::runtime_error("Could not create output file: " + outPath);
	}

	int lineNum = 0;

	uint32_t currAddress = 0x0;

	while (std::getline(inFile, line)) {

		lineNum++;

		std::vector<std::string> tokens = tokenize(line);

		if (tokens.empty()) {
			continue;
		}

		//check if it has label or not?
		if (tokens[0].back() == ':') {

			tokens.erase(tokens.begin());

			//if tokens only contained Label then skip this line 
			if (tokens.empty()) continue;
		}

		//now then label is taken care of identify the instruction 
		std::string mnemonic = tokens[0];

		//guard clause
		if (INSTRUCTION_TABLE.find(mnemonic) == INSTRUCTION_TABLE.end()) {
			throw InvalidInstructionException("Unknown instruction....(in Addembler secondPass)", lineNum);
		}

		InstructionMetadata meta = INSTRUCTION_TABLE.at(mnemonic);
		
		if (meta.expectedOperands != tokens.size() - 1) {
			throw OperandException("Expected operands : " + std::to_string(meta.expectedOperands) + "....(in Assembler secondPass) ", lineNum);
		}

		DecodedInstruction decInst = {};

		decInst.opcode = meta.opcode;
		decInst.funct3 = meta.funct3;
		decInst.funct7 = meta.funct7;

		//building decInst and
		//Error checking for each  individual instruction
		switch (meta.instTy) {

			case InstructionType::R:
				decInst.rd = parseRegister(tokens[1], lineNum);
				decInst.rs1 = parseRegister(tokens[2], lineNum);
				decInst.rs2 = parseRegister(tokens[3], lineNum);
				break;

			case InstructionType::I:
				decInst.rd = parseRegister(tokens[1], lineNum);

				if (meta.opcode == Opcode::LOAD) {
					// e.g. LW x1, 5(x2)  ->  LW x1 5 x2
					decInst.imm = parseImmediate(tokens[2], currAddress, symbolTable, lineNum);
					decInst.rs1 = parseRegister(tokens[3], lineNum);
				}
				else {
					// e.g. ADDI x1, x2, 5  ->  ADDI x1 x2 5
					decInst.rs1 = parseRegister(tokens[2], lineNum);
					decInst.imm = parseImmediate(tokens[3], currAddress, symbolTable, lineNum);
				}
				break;

			case InstructionType::I_SHIFT:
				decInst.rd = parseRegister(tokens[1], lineNum);
				decInst.rs1 = parseRegister(tokens[2], lineNum);
				decInst.imm = parseImmediate(tokens[3], currAddress, symbolTable, lineNum);
				break;

			case InstructionType::S:
				decInst.rs2 = parseRegister(tokens[1], lineNum);
				decInst.imm = parseImmediate(tokens[2], currAddress, symbolTable, lineNum);
				decInst.rs1 = parseRegister(tokens[3], lineNum);
				break;

			case InstructionType::B:
				decInst.rs1 = parseRegister(tokens[1], lineNum);
				decInst.rs2 = parseRegister(tokens[2], lineNum);
				decInst.imm = parseImmediate(tokens[3], currAddress, symbolTable, lineNum);
				if (decInst.imm % 4 != 0) {
					throw AssemblerException("Branch/Jump target must be an address divisable by 4....(in Assembler secondPass). ", lineNum);
				}
				break;

			case InstructionType::U:
				decInst.rd = parseRegister(tokens[1], lineNum);
				decInst.imm = parseImmediate(tokens[2], currAddress, symbolTable, lineNum);
				break;

			case InstructionType::J:
				decInst.rd = parseRegister(tokens[1], lineNum);
				decInst.imm = parseImmediate(tokens[2], currAddress, symbolTable, lineNum);
				if (decInst.imm % 4 != 0) {
					throw AssemblerException("Branch/Jump target must be an address divisable by 4....(in Assembler secondPass). ", lineNum);
				}
				break;

			case InstructionType::SYSTEM:
				//dont need rs1,rs2 or rdw
				break;

			//no need for default no unknown inst will reach till here
		}

		uint32_t macInst = InstructionPacker::packInstruction(decInst, meta.instTy);

		outFile << std::hex << std::setfill('0') << std::setw(8) << macInst << "\n";

		currAddress += 4;
	}

	inFile.close();
	outFile.close();

	return outPath;
}