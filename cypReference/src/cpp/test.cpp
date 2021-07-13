#include "cyp_timer.hpp"
#include "cyp_vector.hpp"

int main()
{
	std::vector<int> a = { 1,2,3,4,5,6,7,8,9,10 };
	cyp::timer::Timer timer;
	timer.start();
	
	for (int i = 0; i < 100000; ++i)
	{
		i++;
	}

	std::cout << timer.getTime<std::chrono::nanoseconds>();
	
	cyp::vector::isContain<int>(a, 1);
}