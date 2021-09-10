#include <cyp_encrypt.hpp>

int main()
{
	cyp::encrypt::Aes aes;
	auto a = aes.cbcEncrypt_hex256("kim ouk ja");
	std::cout << std::get<0>(a) << std::endl;
	std::cout << std::get<1>(a) << std::endl;
	std::cout << std::get<2>(a) << std::endl;

	auto b = aes.cbcDecrypt_hex256(std::get<0>(a), std::get<1>(a), std::get<2>(a));
	std::cout << b << std::endl;

}