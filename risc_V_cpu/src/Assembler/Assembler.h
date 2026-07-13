#pragma once

#include <cstdint>
#include <unordered_map>
#include <string>
#include <vector>

namespace Assembler { 

	std::string assemble(const std::string& filrPath);

	std::unordered_map<std::string, std::uint32_t> firstPass(const std::string& filePath);

	std::string secondPass(const std::string& filePath , std::unordered_map<std::string , uint32_t>& symbolTable);

	std::vector<std::string> tokenize(std::string& line);

	uint32_t parseRegister(const std::string& regStr, int lineNum);

	int32_t parseImmediate(const std::string& token , uint32_t currAddress,
		const std::unordered_map<std::string , uint32_t>& symbolTable , int lineNum);

};