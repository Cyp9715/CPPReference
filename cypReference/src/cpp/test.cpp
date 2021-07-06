#include "cyp_encrypt.hpp"
#include "cyp_communication.hpp"
#include "cyp_hash.hpp"

int main()
{
	cyp::communication::Tcp tcp;
	cyp::encrypt::Aes aes;

	cyp::hash::Sha sha;
	sha.strToSHA2_512("123213");
}