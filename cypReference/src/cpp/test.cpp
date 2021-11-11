#include "cyp_hash.hpp"

int main()
{
	cyp::hash::Pbkdf2 pbkdf2;
	cyp::hash::Hkdf hkdf;

	std::cout << pbkdf2.strToPbkdf2<CryptoPP::SHA256>("123123", "sss", 1024) << std::endl;
	std::cout << hkdf.strToHkdf<CryptoPP::SHA256>("password", "salt", "HKDF key derivation") << std::endl;
}