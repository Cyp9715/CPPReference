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

		void Timer::Start()
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

		int FpsCounter::LoopCounting()
		{
			++_tempFps;
			if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _loopStart) >= std::chrono::seconds(1))
			{
				_loopFps = _tempFps;
				_tempFps = 0;
				_loopStart = std::chrono::system_clock::now();
				return _loopFps;
			}

			return _loopFps;
		}


		void FpsCounter::StartTimeCounting()
		{
			_start = std::chrono::system_clock::now();
		}

		float FpsCounter::EndTimeCounting()
		{
			_end = std::chrono::system_clock::now();
			std::chrono::milliseconds delta = std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start);

			if (delta.count() > 0)
				return MILISECOND / delta.count();

			return 0;
		}

		void CallbackTimer::Regist(int miliseconds, std::function<void()>& func)
		{
			std::thread([miliseconds, &func]()
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
					func();
				}).detach();
		}

		void CallbackTimer::Regist_loop(int miliseconds, std::function<void()>& func, bool& isLoop)
		{
			std::thread([miliseconds, &func, &isLoop]()
				{
					do
					{
						std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
						func();
					} while (isLoop == true);
				}).detach();
		}

		void CallbackTimer::Regist_loop_thread(int& miliseconds, std::function<void()>& func, bool& isLoop, int& maxThreadCount)
		{
			if (isRunningTimer)
				throw("Callback loop function is already in progress. Create a new CallbackTimer objectand proceed.");

			isRunningTimer = true;
			std::thread([this, &miliseconds, &func, &isLoop, &maxThreadCount]()
				{
					do
					{
						while (true)
						{
							// 해당 부분 수정해야 됨 매우 비효율적.
							if (currentThreadCount >= maxThreadCount)
								std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
							else
								break;
						}

						_m.lock();
						++currentThreadCount;
						_m.unlock();

						std::thread([this, &miliseconds, &func]()
							{
								std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
								
								func();

								_m.lock();
								--currentThreadCount;
								_m.unlock();

							}).detach();
					} while (isLoop == true);

					isRunningTimer = false;
				}).detach();
		}

		void CallbackTimer::Regist_loop_thread(int&& miliseconds, std::function<void()>& func, bool& isLoop, int&& maxThreadCount)
		{
			if (isRunningTimer)
				throw("Callback loop function is already in progress. Create a new CallbackTimer objectand proceed.");

			isRunningTimer = true;
			std::thread([this, miliseconds, &func, &isLoop, maxThreadCount]()
				{
					do
					{
						// 해당 부분 수정해야 됨 매우 비효율적.
						while (true)
						{
							if (currentThreadCount >= maxThreadCount)
								std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
							else
								break;
						}

						_m.lock();
						++currentThreadCount;
						_m.unlock();

						std::thread([this, miliseconds, &func]()
							{
								std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));

								func();

								_m.lock();
								--currentThreadCount;
								_m.unlock();

							}).detach();
					} while (isLoop == true);

					isRunningTimer = false;
				}).detach();

		}
	}
}