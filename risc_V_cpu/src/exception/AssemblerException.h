#pragma once

#include <stdexcept>
#include <string>

class AssemblerException : public std::runtime_error {

public:

	explicit AssemblerException(const std::string& msg , int line) : 
		std::runtime_error("Assambler Error [Line : " + std::to_string(line) + "] : " + msg )  {}

};

class InvalidInstructionException : public AssemblerException {

public:

	explicit InvalidInstructionException(const std::string& msg , int line) 
		: AssemblerException(msg , line) {}

};

class SymbolNotFoundException : public AssemblerException{

public:

	explicit SymbolNotFoundException(const std::string& msg, int line)
		: AssemblerException(msg, line) {}
};

class ImmediateOutOfRangeException : public AssemblerException {

public:

	explicit ImmediateOutOfRangeException(const std::string& msg, int line)
		: AssemblerException(msg, line) {}

};

class OperandException : public AssemblerException {

public:

	explicit OperandException(const std::string& msg, int line)
		: AssemblerException(msg, line) {}

};

class InvalidRegisterException : public AssemblerException {

public:

	explicit InvalidRegisterException(const std::string& msg, int line)
		: AssemblerException(msg, line) {}

};

class InvalidAddressException : public AssemblerException {

public:

	explicit InvalidAddressException(const std::string& msg, int line)
		: AssemblerException(msg, line) {}

};