#pragma once
#include "cyp_common.hpp"
#include "cryptopp/hex.h"

namespace cyp
{
	namespace convert
	{
		class Hex
		{
		public:
			// B1B2 -> std::string { 10110001, 10110010 } == { 0xB1, 0xB2 }
			std::string StrToHex(std::string& str);
			// unsigned char[6] {0xFF, 0xFD, 0xFC, 0xCF, 0xDF, 0xFF} -> FFFDFCCFDFFF
			std::string HexToStr(unsigned char* str, size_t size);
		};
	}
}	