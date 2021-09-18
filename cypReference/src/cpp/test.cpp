#include "cyp_timer.hpp"

class A
{
public:
	void AAA()
	{
		std::cout << "AAA" << std::endl;
	}
	
	void BBB()
	{
		std::cout << "BBB" << std::endl;
	}
};

int main()
{
	A a;
	int temp = 10;

	std::function<void()> func = std::bind(&A::AAA, a);

	cyp::timer::CallbackTimer call;
	bool trr = true;
	call.regist_loop(300, func, trr);

	std::cout << "If you want to print BBB, enter anything." << std::endl;
	std::cin >> temp;
	func = std::bind(&A::BBB, a);

	//std::cout << "If you want an error to occur, enter anything." << std::endl;
	//std::cin >> temp;
	//func = nullptr;

	std::cout << "stop thread" << std::endl;
	std::cin >> temp;
	trr = false;

	std::cin >> temp;
}