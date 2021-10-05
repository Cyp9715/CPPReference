#include "cyp_encrypt.hpp"

class A
{
public:
	int a;
	int b;
	int c;
};

int main()
{
	cyp::encrypt::Aes aes;
	auto a = aes.cbcEncrypt_hex256("123");
}