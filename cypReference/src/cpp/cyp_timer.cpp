#include "cyp_timer.hpp"

namespace cyp
{
	namespace timer
	{
		template long long Timer::getTime<std::chrono::seconds>();

		void Timer::updateCurrentTime()
		{
			_current = std::chrono::system_clock::now();
		}
		void Timer::start()
		{
			_start = std::chrono::system_clock::now();
		}

		long long Timer::getHour()
		{
			updateCurrentTime();
			std::chrono::hours second = std::chrono::duration_cast<std::chrono::hours>(_current - _start);
			return second.count();
		}

		long long Timer::getMinute()
		{
			updateCurrentTime();
			std::chrono::minutes minute = std::chrono::duration_cast<std::chrono::minutes>(_current - _start);
			return minute.count();
		}

		long long Timer::getSecond()
		{
			updateCurrentTime();
			std::chrono::milliseconds second = std::chrono::duration_cast<std::chrono::seconds>(_current - _start);
			return second.count();
		}

		long long Timer::getMiliSecond()
		{
			updateCurrentTime();
			std::chrono::milliseconds mili = std::chrono::duration_cast<std::chrono::milliseconds>(_current - _start);
			return mili.count();
		}

		long long Timer::getNanoSecond()
		{
			updateCurrentTime();
			std::chrono::nanoseconds mili = _current - _start;
			auto a = getTime<std::chrono::seconds>();
			return mili.count();
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