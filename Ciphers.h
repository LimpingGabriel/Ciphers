#pragma once
#include <iostream>

namespace Ciphers::Classic {
	std::string caesar(std::string& inString, int shift, bool encode);
}