#include "cyp_timer.hpp"
#include "cyp_vector.hpp"
#include "cyp_hash.hpp"
#include <future>

int main()
{
    cyp::timer::FpsCounter counter;

    while (true)
    {
        counter.startTimeCounting();

        std::vector<int> v_int;

        int sum = 10;
        for (int i = 0; i < 2000000; ++i)
        {
            ++sum;
            v_int.push_back(sum);
        }
        
        //std::cout << counter.loopCounting() << std::endl;
        std::cout << counter.endTimeCounting() << std::endl;
    }
}