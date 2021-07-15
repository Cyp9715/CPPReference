#include "cyp_timer.hpp"

namespace cyp
{
	namespace timer
	{
#if _HAS_CXX20
		template long long Timer::getTime<std::chrono::months>();
		template long long Timer::getTime<std::chrono::years>();
		template long long Timer::getTime<std::chrono::weeks>();
		template long long Timer::getTime<std::chrono::days>();
#endif
		template long long Timer::getTime<std::chrono::hours>();
		template long long Timer::getTime<std::chrono::minutes>();
		template long long Timer::getTime<std::chrono::seconds>();
		template long long Timer::getTime<std::chrono::milliseconds>();
		template long long Timer::getTime<std::chrono::microseconds>();
		template long long Timer::getTime<std::chrono::nanoseconds>();

		void Timer::start()
		{
			_start = std::chrono::system_clock::now();
		}

		template<typename T>
		long long Timer::getTime()
		{
			_current = std::chrono::system_clock::now();
			T t = std::chrono::duration_cast<T>(_current - _start);
			return t.count();
		}

		void FpsCounter::init()
		{
			_fps = 0;
			_start = std::chrono::high_resolution_clock::now();
		}

		float FpsCounter::counting()
		{
			++_fps;
			if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - _start) >= std::chrono::seconds{ 1 }) 
			{
				_start = std::chrono::high_resolution_clock::now();
				std::cout << "FPS: " << _fps << std::endl;
				_fps = 0;
			}

			return 0.0f;
		}
	}
}