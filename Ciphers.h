#pragma once
#include <iostream>

namespace ciphers::classic {
	std::string caesar(std::string& inString, int shift, bool encode);
}
namespace ciphers::modern {
	std::string solitaire(std::string& inText, std::string& key, bool encode);
}