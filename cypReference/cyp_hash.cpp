#include "cyp_hash.hpp"

namespace cyp
{
	namespace hash
	{
		std::string MD::strToMD5(const std::string& str)
		{
			CryptoPP::byte digest[CryptoPP::Weak::MD5::DIGESTSIZE];

			CryptoPP::Weak::MD5 hash;
			hash.CalculateDigest(digest, (const CryptoPP::byte*)str.c_str(), str.length());

			CryptoPP::HexEncoder encoder;
			std::string output;

			encoder.Attach(new CryptoPP::StringSink(output));
			encoder.Put(digest, sizeof(digest));
			encoder.MessageEnd();

			return output;
		}

		std::string MD::fileToMD5(const std::string filePath)
		{
			CryptoPP::Weak::MD5 md;
			const size_t size = CryptoPP::Weak::MD5::DIGESTSIZE * 2;
			CryptoPP::byte buf[size] = { 0 };
			CryptoPP::FileSource filesource(
				filePath.c_str(), true,
				new CryptoPP::HashFilter(
					md, new CryptoPP::HexEncoder(new CryptoPP::ArraySink(buf, size))));
			std::string output = std::string(reinterpret_cast<const char*>(buf), size);

			return output;
		}

		std::string SHA::strToSHA1(const std::string& str)
		{
			CryptoPP::SHA1 hash;
			std::string output;

			CryptoPP::StringSource s(str, true, new CryptoPP::HashFilter(hash,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(output))));

			return output;
		}

		std::string SHA::fileToSHA1(const std::string& filePath)
		{
			CryptoPP::SHA1 hash;
			std::string output;

			CryptoPP::FileSource f(filePath.c_str(), true,
				new CryptoPP::HashFilter(hash,
					new CryptoPP::HexEncoder(new
						CryptoPP::StringSink(output))));

			return output;
		}

		std::string SHA::strToSHA2_256(const std::string& str)
		{
			CryptoPP::SHA256 hash;
			std::string output;

			CryptoPP::StringSource s(str, true, new CryptoPP::HashFilter(hash,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(output))));

			return output;
		}

		std::string SHA::fileToSHA2_256(const std::string& filePath)
		{
			CryptoPP::SHA256 hash;
			std::string output;

			CryptoPP::FileSource f(filePath.c_str(), true,
				new CryptoPP::HashFilter(hash,
					new CryptoPP::HexEncoder(new
						CryptoPP::StringSink(output))));

			return output;
		}

		std::string SHA::strToSHA2_512(const std::string& str)
		{
			CryptoPP::SHA512 hash;
			std::string output;

			CryptoPP::StringSource s(str, true, new CryptoPP::HashFilter(hash,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(output))));

			return output;
		}

		std::string SHA::fileToSHA2_512(const std::string& filePath)
		{
			CryptoPP::SHA512 hash;
			std::string output;

			CryptoPP::FileSource f(filePath.c_str(), true,
				new CryptoPP::HashFilter(hash,
					new CryptoPP::HexEncoder(new
						CryptoPP::StringSink(output))));

			return output;
		}

		std::string SHA::strToSHA3_256(const std::string& str)
		{
			CryptoPP::SHA3_256 hash;
			std::string output;

			CryptoPP::StringSource s(str, true, new CryptoPP::HashFilter(hash,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(output))));

			return output;
		}

		std::string SHA::fileToSHA3_256(const std::string& filePath)
		{
			CryptoPP::SHA3_256 hash;
			std::string output;

			CryptoPP::FileSource f(filePath.c_str(), true,
				new CryptoPP::HashFilter(hash,
					new CryptoPP::HexEncoder(new
						CryptoPP::StringSink(output))));

			return output;
		}

		std::string SHA::strToSHA3_512(const std::string& str)
		{
			CryptoPP::SHA3_512 hash;
			std::string output;

			CryptoPP::StringSource s(str, true, new CryptoPP::HashFilter(hash,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(output))));

			return output;
		}

		std::string SHA::fileToSHA3_512(const std::string& filePath)
		{
			CryptoPP::SHA3_512 hash;
			std::string output;

			CryptoPP::FileSource f(filePath.c_str(), true,
				new CryptoPP::HashFilter(hash,
					new CryptoPP::HexEncoder(new
						CryptoPP::StringSink(output))));

			return output;
		}
	}

}