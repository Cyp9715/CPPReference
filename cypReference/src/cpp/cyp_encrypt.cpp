#include "cyp_encrypt.hpp"

namespace cyp
{
	namespace encrypt
	{
		// example code, need analysis.
		Aes::Aes()
		{

		}

		std::tuple<std::string, std::string, std::string> Aes::cbcEncrypt(const std::string& plainText)
		{
			std::string cipher;
			std::string output_cipher, output_iv, output_key;

			CryptoPP::AutoSeededRandomPool prng;

			CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH];
			prng.GenerateBlock(key, sizeof(key));

			CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];
			prng.GenerateBlock(iv, sizeof(iv));

			CryptoPP::StringSource(key, sizeof(key), true,
				new CryptoPP::HexEncoder(
					new CryptoPP::StringSink(output_key)
				)
			);

			CryptoPP::StringSource(iv, sizeof(iv), true,
				new CryptoPP::HexEncoder(
					new CryptoPP::StringSink(output_iv)
				)
			);

			try
			{
				CryptoPP::CBC_Mode< CryptoPP::AES >::Encryption e;
				e.SetKeyWithIV(key, sizeof(key), iv);

				CryptoPP::StringSource s(plainText, true,
					new CryptoPP::StreamTransformationFilter(e,
						new CryptoPP::StringSink(cipher)
					)
				);
			}
			catch (const CryptoPP::Exception& e)
			{
				std::cerr << e.what() << std::endl;
				exit(1);
			}


			CryptoPP::StringSource(cipher, true,
				new CryptoPP::HexEncoder(
					new CryptoPP::StringSink(output_cipher)
				)
			);

			std::tuple<std::string, std::string, std::string> output = std::make_tuple(output_key, output_iv, output_cipher);

			return output;
		}


		std::string Aes::cbcDecrypt(const std::string& keyText, const std::string& ivText, const std::string& cipherText)
		{

			return std::string();
		}
	}
}