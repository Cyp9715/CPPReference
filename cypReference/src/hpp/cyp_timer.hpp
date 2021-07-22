#pragma once

#include "cyp_common.hpp"
#include <math.h>
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

		public:
			void start();

			template<typename T>
			long long getTime();
		};

		class FpsCounter
		{
		private:
			const float MILISECOND = 1000.0;

			int _tempFps = 0;
			int _loopFps = 0;
			float _fps = 0;

			std::chrono::system_clock::time_point _loopStart;

			std::chrono::system_clock::time_point _start;
			std::chrono::system_clock::time_point _end;

		public:
			// The return criterion is how many loop statements were executed per second.
			// i.e, only use in loop.
			int loopCounting();

			// The Return criteria, number of times a second is divided by running time.
			// i.e., can measure FPS indirectly even if not loop
			void startTimeCounting();
			float endTimeCounting();
		};
	}
}