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

		int FpsCounter::loopCounting()
		{
			++_simplefps;
			if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _simpleStart) >= std::chrono::seconds(1))
			{
				_simplefpsR = _simplefps;
				_simplefps = 0;
				_simpleStart = std::chrono::system_clock::now();
				return _simplefpsR;
			} 
			
			return _simplefpsR;
		}


		void FpsCounter::timeCountingStart()
		{
			_start = std::chrono::system_clock::now();
		}

		float FpsCounter::timeCountingEnd()
		{
			_end = std::chrono::system_clock::now();
			std::chrono::milliseconds delta = std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start);
			
			if(delta.count() > 0)
				return MILISECOND / delta.count();
			
			return 0;
		}
	}
}