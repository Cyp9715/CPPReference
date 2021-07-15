#include "cyp_timer.hpp"
#include "cyp_vector.hpp"
#include "cyp_hash.hpp"
#include <future>

int main()
{
    cyp::timer::FpsCounter counter;

    while (true)// your main loop. could also be the idle() function in glut or whatever
    {
        int sum = 10;
        for (int i = 0; i < 2000000; ++i)
        {
            sum += i;
            sum -= i;         sum += i;
            sum -= i;         sum += i;
            sum -= i;         sum += i;
            sum -= i;         sum += i;
            sum -= i;
        }
        
        std::cout << counter.loopCounting() << std::endl;
    }
}