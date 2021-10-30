#include "cyp_encrypt.hpp"

int main()
{
	cyp::encrypt::Aes aed;
	auto aa = aed.cbcEncrypt_hex256("테스트문자열 : my name is C++ 20");
	std::cout << std::get<0>(aa) << std::endl;
	std::cout << std::get<1>(aa) << std::endl;
	std::cout << std::get<2>(aa) << std::endl;
	aed.cbcDecrypt_hex256(std::get<0>(aa), std::get<1>(aa), std::get<2>(aa));
}