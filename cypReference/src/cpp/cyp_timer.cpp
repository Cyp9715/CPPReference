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
	}
}