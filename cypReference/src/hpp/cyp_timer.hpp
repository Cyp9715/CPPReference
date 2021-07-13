#pragma once

#include "cyp_common.hpp"
#include <chrono>

namespace cyp
{
	namespace timer
	{
		class Timer
		{
		private:
			std::chrono::system_clock::time_point _start;
			std::chrono::system_clock::time_point _current;

		private:
			void updateCurrentTime();

		public:
			void start();
			long long getHour();
			long long getMinute();
			long long getSecond();
			long long getMiliSecond();
			long long getNanoSecond();
			
			template<typename T>
			long long getTime();
		};

		class FpsCounter
		{
		public:
			void init();
			float counting();
		};
	}
}