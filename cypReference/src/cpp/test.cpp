#include "cyp_sharedMemory.hpp"

class A
{
public:
	int a;
	int b;
	int c;
};

int main()
{
	cyp::sharedMemory::Client<A> sharedMemory;
	sharedMemory.start("kim");
	auto k = sharedMemory.getMemory();

	std::cout << k->a << std::endl;
	std::cout << k->b << std::endl;
	std::cout << k->c << std::endl;

	int a;
	
	std::cin >> a;
}