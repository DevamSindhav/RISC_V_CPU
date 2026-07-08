#pragma once

#include "../bus/bus.h"

#include <string>


namespace Loader {

	void loadProgram(Bus& bus, const std::string& filePath);

};