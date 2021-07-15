#include "cyp_timer.hpp"
#include "cyp_vector.hpp"
#include "cyp_hash.hpp"
#include <future>

int main()
{
    cyp::timer::FpsCounter counter;

    while (true)// your main loop. could also be the idle() function in glut or whatever
    {
        counter.timeCountingStart();
        //std::cout << counter.loopCounting() << std::endl;

        int sum = 10;
        for (int i = 0; i < 20000000; ++i)
        {
        }
        
        std::cout << counter.timeCountingEnd() << std::endl;
    }
}