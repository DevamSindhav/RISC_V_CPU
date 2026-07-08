#pragma once

#include <stdexcept>
#include<string>

class HardwareException : public std::runtime_error {

public:
	explicit HardwareException(const std::string& msg) : std::runtime_error(msg){}

};

class MemoryException : public HardwareException {

public:
	explicit MemoryException(const std::string& msg) : HardwareException("Memory fault : " + msg) {}

};

class DecoderException : public HardwareException {

public:
	explicit DecoderException(const std::string& msg) : HardwareException("Decode fault : " + msg) {}

};

class SysCallException : public HardwareException {

public:
	explicit SysCallException(const std::string& msg) : HardwareException("OS fault : " + msg) {}

};