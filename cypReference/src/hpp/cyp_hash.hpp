#pragma once

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include "cryptopp/cryptlib.h"
#include "cryptopp/sha.h"
#include "cryptopp/sha3.h"
#include "cryptopp/md5.h"
#include "cryptopp/hex.h"
#include "cryptopp/files.h"
#include "cyp_common.hpp"

// PBKDF2
#include "cryptopp/pwdbased.h"

// HKDF
#include "cryptopp/hkdf.h"

#include "cryptopp/blake2.h"


#pragma comment(lib, "cryptlib.lib")

namespace cyp
{
	namespace hash
	{
		std::string errorType(CryptoPP::Exception::ErrorType exception);
		// The MD algorithm is not secure.
		class Md
		{
		public:
			std::string strToMD5(const std::string& str);
			std::string fileToMD5(const std::string filePath);
		};

		// The SHA1 algorithm is not secure.
		class Sha
		{
		public:
			template <typename T>
			std::string strToSha(const std::string& str);
			template <typename T>
			std::string fileToSha(const std::string& filePath);
		};

		class Pbkdf2
		{
		public:
			// If time > 0.0 then DeriveKey will run for the specified amount of time. 
			// If time is 0.0 then DeriveKey will run for the specified number of iterations.
			template <typename T>
			std::string strToPbkdf2(const std::string& str, const std::string& salt, unsigned int iterate, float time = 0.0f);
		};

		class Hkdf
		{
		public:
			template <typename T>
			std::string strToHkdf(const std::string& str, const std::string& salt, const std::string& info);
		};
	}
}