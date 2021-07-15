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

		public:
			void start();

			template<typename T>
			long long getTime();
		};

		class FpsCounter
		{
		private:
			int _fps;
			std::chrono::time_point<std::chrono::steady_clock> _start;
			std::chrono::system_clock::time_point _current;

		public:
			void init();
			float counting();
		};
	}
}