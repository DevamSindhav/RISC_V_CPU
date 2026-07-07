#pragma once
#include<cstdint>
#include<iostream>
#include<array>

// for now using registers and vars to pass to syscallHandler
//but will require whole cpu functions in future.....
class SysCallHandler {

public:

	SysCallHandler();

	//to handle ecall it needs access to registers 
	// and halt to halt make cpu stop execution
	static void handleECALL(std::array<uint32_t, 32>& registers , bool& isCpuHalted);

	//same fot ebreak may need registers and pc to display their values
	static void handleEBREAK(std::array<uint32_t , 32>& registers , uint32_t pc);

};