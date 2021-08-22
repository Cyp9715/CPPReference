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



			std::string recovered;

			std::tuple<std::string, std::string, std::string> output = std::make_tuple(output_key, output_iv, output_cipher);

			return output;
		}


		std::string Aes::cbcDecrypt(const std::string& keyText, const std::string& ivText, const std::string& cipherText)
		{
			std::string keyHex;
			std::string ivHex;
			std::string cipherHex;
			std::string plainText;


			CryptoPP::StringSource(keyText, true,
				new CryptoPP::HexDecoder(
					new CryptoPP::StringSink(keyHex)
				)
			);

			CryptoPP::StringSource(ivText, true,
				new CryptoPP::HexDecoder(
					new CryptoPP::StringSink(ivHex)
				)
			);

			CryptoPP::StringSource(cipherText, true,
				new CryptoPP::HexDecoder(
					new CryptoPP::StringSink(cipherHex)
				)
			);

			unsigned char tempKey[16];
			unsigned char tempIv[16];
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

				std::cout << "recovered text: " << plainText << std::endl;
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