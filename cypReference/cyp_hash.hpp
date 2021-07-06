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
		// The MD algorithm is not secure.
		class MD
		{
		public:
			/* MD5 */
			std::string strToMD5(const std::string& str);
			std::string fileToMD5(const std::string filePath);
		};

		// The SHA1 algorithm is not secure.
		class SHA
		{
		public:
			/* SHA1 */
			std::string strToSHA1(const std::string& str);
			std::string fileToSHA1(const std::string& filePath);

			/* SHA2 */
			std::string strToSHA2_256(const std::string& str);
			std::string fileToSHA2_256(const std::string& filePath);
			std::string strToSHA2_512(const std::string& str);
			std::string fileToSHA2_512(const std::string& filePath);

			/* SHA3 */
			std::string strToSHA3_256(const std::string& str);
			std::string fileToSHA3_256(const std::string& filePath);
			std::string strToSHA3_512(const std::string& str);
			std::string fileToSHA3_512(const std::string& filePath);
		};
	}

}