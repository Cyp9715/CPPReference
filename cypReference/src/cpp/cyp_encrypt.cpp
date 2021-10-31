#include "cyp_encrypt.hpp"

namespace cyp
{
	namespace encrypt
	{
		// example code, need analysis.
		Aes::Aes()
		{

		}

		std::tuple<std::string, std::string, std::string> Aes::cbcEncrypt_hex256(const std::string& plainText)
		{
			std::string cipherHex;
			std::string cipherText, ivText, keyText;

			CryptoPP::AutoSeededRandomPool prng;

			CryptoPP::byte key[32];
			prng.GenerateBlock(key, sizeof(key));

			CryptoPP::byte iv[32];
			prng.GenerateBlock(iv, sizeof(iv));

			CryptoPP::StringSource ss_key(key, sizeof(key), true,
				new CryptoPP::HexEncoder(
					new CryptoPP::StringSink(keyText)
				)
			);

			CryptoPP::StringSource ss_iv(iv, sizeof(iv), true,
				new CryptoPP::HexEncoder(
					new CryptoPP::StringSink(ivText)
				)
			);

			try
			{
				CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption e;
				e.SetKeyWithIV(key, sizeof(key), iv);

				CryptoPP::StringSource s(plainText, true,
					new CryptoPP::StreamTransformationFilter(e,
						new CryptoPP::StringSink(cipherHex)
					)
				);
			}
			catch (const CryptoPP::Exception& e)
			{
				std::cerr << e.what() << std::endl;
				exit(1);
			}


			CryptoPP::StringSource ss_cipher(cipherHex, true,
				new CryptoPP::HexEncoder(
					new CryptoPP::StringSink(cipherText)
				)
			);
	
			std::tuple<std::string, std::string, std::string> output = std::make_tuple(keyText, ivText, cipherText);

			return output;
		}


		std::string Aes::cbcDecrypt_hex256(const std::string& keyText, const std::string& ivText, const std::string& cipherText)
		{
			std::string keyHex;
			std::string ivHex;
			std::string cipherHex;
			std::string plainText;

			CryptoPP::StringSource ss_key(keyText, true,
				new CryptoPP::HexDecoder(
					new CryptoPP::StringSink(keyHex)
				)
			);

			CryptoPP::StringSource ss_iv(ivText, true,
				new CryptoPP::HexDecoder(
					new CryptoPP::StringSink(ivHex)
				)
			);

			CryptoPP::StringSource ss_cipher(cipherText, true,
				new CryptoPP::HexDecoder(
					new CryptoPP::StringSink(cipherHex)
				)
			);

			unsigned char tempKey[32];
			unsigned char tempIv[32];
			std::copy(keyHex.begin(), keyHex.end(), tempKey);
			std::copy(ivHex.begin(), ivHex.end(), tempIv);

			try
			{
				CryptoPP::CBC_Mode< CryptoPP::AES >::Decryption d;
				d.SetKeyWithIV(tempKey, keyHex.size(), tempIv);

				CryptoPP::StringSource s(cipherHex, true,
					new CryptoPP::StreamTransformationFilter(d,
						new CryptoPP::StringSink(plainText)
					)
				);
			}
			catch (const CryptoPP::Exception& e)
			{
				std::cerr << e.what() << std::endl;
				exit(1);
			}
			return plainText;
		}
	}
}