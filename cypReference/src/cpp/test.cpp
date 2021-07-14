#include "cyp_timer.hpp"
#include "cyp_vector.hpp"
#include "cyp_hash.hpp"

int main()
{
	cyp::hash::Sha sha;
	std::cout << sha.strToSha<CryptoPP::SHA1>("123");
	std::cout << sha.fileToSha<CryptoPP::SHA224>("123");
}