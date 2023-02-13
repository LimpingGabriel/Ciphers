#include <iostream>

namespace Ciphers::Classic {
	std::string caesar(std::string& inString, int shift, bool encode) {
		const char* lower = "abcdefghijklmnopqrstuvwxyz";
		const char* upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		if (!encode) {
			shift = 0 - shift;
		}
		char newChar;
		int normalizedChar;

		bool charUpper;
		bool charLower;

		std::string outString = std::string();
		for (auto &currentChar : inString) {
			charUpper = isupper(currentChar);
			charLower = islower(currentChar);
			normalizedChar = charLower ? (int)currentChar - 97 : (int)currentChar - 65;
			const char* usealpha = charLower ? lower : upper;
			bool shouldShift = charLower || charUpper;
			if (shouldShift) {
				if (normalizedChar + shift < 0) {
					newChar = usealpha[normalizedChar + shift + 26];
				}
				else if (normalizedChar + shift > 25) {
					newChar = usealpha[normalizedChar + shift - 26];
				}
				else {
					newChar = usealpha[normalizedChar + shift];
				}
			}
			else {
				newChar = currentChar;
			}
			outString += newChar;
		}
		return outString;
	}
}