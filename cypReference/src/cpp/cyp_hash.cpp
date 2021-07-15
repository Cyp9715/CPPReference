#include "cyp_hash.hpp"

namespace cyp
{
	namespace hash
	{
		template std::string Sha::strToSha<CryptoPP::SHA1>(const std::string& str);
		template std::string Sha::strToSha<CryptoPP::SHA224>(const std::string& str);
		template std::string Sha::strToSha<CryptoPP::SHA256>(const std::string& str);
		template std::string Sha::strToSha<CryptoPP::SHA384>(const std::string& str);
		template std::string Sha::strToSha<CryptoPP::SHA512>(const std::string& str);
		template std::string Sha::strToSha<CryptoPP::SHA3_224>(const std::string& str);
		template std::string Sha::strToSha<CryptoPP::SHA3_256>(const std::string& str);
		template std::string Sha::strToSha<CryptoPP::SHA3_384>(const std::string& str);
		template std::string Sha::strToSha<CryptoPP::SHA3_512>(const std::string& str);

		template std::string Sha::fileToSha<CryptoPP::SHA1>(const std::string& str);
		template std::string Sha::fileToSha<CryptoPP::SHA224>(const std::string& str);
		template std::string Sha::fileToSha<CryptoPP::SHA256>(const std::string& str);
		template std::string Sha::fileToSha<CryptoPP::SHA384>(const std::string& str);
		template std::string Sha::fileToSha<CryptoPP::SHA512>(const std::string& str);
		template std::string Sha::fileToSha<CryptoPP::SHA3_224>(const std::string& str);
		template std::string Sha::fileToSha<CryptoPP::SHA3_256>(const std::string& str);
		template std::string Sha::fileToSha<CryptoPP::SHA3_384>(const std::string& str);
		template std::string Sha::fileToSha<CryptoPP::SHA3_512>(const std::string& str);

		template <typename T>
		std::string Sha::strToSha(const std::string& str)
		{
			T hash;
			std::string output;

			CryptoPP::StringSource s(str, true, new CryptoPP::HashFilter(hash,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(output))));

			return output;
		}

		template <typename T>
		std::string Sha::fileToSha(const std::string& filePath)
		{
			T hash;
			std::string output;

			try
			{
				CryptoPP::FileSource f(filePath.c_str(), true,
					new CryptoPP::HashFilter(hash,
						new CryptoPP::HexEncoder(new
							CryptoPP::StringSink(output))));
			}
			catch (CryptoPP::FileStore::OpenErr const& e)
			{
				CryptoPP::Exception::ErrorType errorMsg = e.GetErrorType();
				output = "Error : fileToSha() = " + errorType(errorMsg);
				return output;
			}

			return output;
		}

		std::string Md::strToMD5(const std::string& str)
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

		std::string Md::fileToMD5(const std::string filePath)
		{
			CryptoPP::Weak::MD5 md;
			std::string output;
			const size_t size = CryptoPP::Weak::MD5::DIGESTSIZE * 2;
			CryptoPP::byte buf[size] = { 0 };
			try
			{
				CryptoPP::FileSource filesource(
					filePath.c_str(), true,
					new CryptoPP::HashFilter(
						md, new CryptoPP::HexEncoder(new CryptoPP::ArraySink(buf, size))));
			}
			catch (CryptoPP::FileStore::OpenErr const& e)
			{
				CryptoPP::Exception::ErrorType errorMsg = e.GetErrorType();
				output = "Error : fileToMD5() = " + errorType(errorMsg);
				return output;
			}

			output = std::string(reinterpret_cast<const char*>(buf), size);

			return output;
		}

		std::string errorType(CryptoPP::Exception::ErrorType exception)
		{
			std::string output;

			switch (exception)
			{
			case CryptoPP::Exception::ErrorType::NOT_IMPLEMENTED:
				output = "NOT_IMPLEMENTED";
				break;

			case CryptoPP::Exception::ErrorType::INVALID_ARGUMENT:
				output = "INVALID_ARGUMENT";
				break;

			case CryptoPP::Exception::ErrorType::CANNOT_FLUSH:
				output = "CANNOT_FLUSH";
				break;

			case CryptoPP::Exception::ErrorType::DATA_INTEGRITY_CHECK_FAILED:
				output = "DATA_INTEGRITY_CHECK_FAILED";
				break;

			case CryptoPP::Exception::ErrorType::INVALID_DATA_FORMAT:
				output = "INVALID_DATA_FORMAT";
				break;

			case CryptoPP::Exception::ErrorType::IO_ERROR:
				output = "IO_ERROR";
				break;

			default:
				output = "OTHER_ERROR";
				break;
			}

			return output;
		}
	}

}