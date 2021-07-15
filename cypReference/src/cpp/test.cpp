#include "cyp_timer.hpp"
#include "cyp_vector.hpp"
#include "cyp_hash.hpp"

int main()
{
	cyp::timer::FpsCounter counter;
	
	while (true)
	{
		int sum = 10;
		for (int i = 0; i < 10000000; ++i)
		{
			sum *= i;
			sum *= i;
			sum *= i;
			sum *= i;
			sum *= i;
			sum *= i;
			sum *= i;
		}
		counter.counting();
	}
}