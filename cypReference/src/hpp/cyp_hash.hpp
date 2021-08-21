#pragma once

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include "cryptopp/cryptlib.h"
#include "cryptopp/sha.h"
#include "cryptopp/sha3.h"
#include "cryptopp/md5.h"
#include "cryptopp/hex.h"
#include "cryptopp/files.h"


namespace cyp
{
	namespace hash
	{
		std::string errorType(CryptoPP::Exception::ErrorType exception);

		// The MD algorithm is not secure.
		class Md
		{
		public:
			/* MD5 */
			std::string strToMD5(const std::string& str);
			std::string fileToMD5(const std::string filePath);
		};

		// The SHA1 algorithm is not secure.
		class Sha
		{
		public:
			/* SHA */
			template <typename T>
			std::string strToSha(const std::string& str);
			template <typename T>
			std::string fileToSha(const std::string& filePath);
		};
	}

}