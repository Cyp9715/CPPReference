#pragma once
#include <cyp_common.hpp>
#include <vector>
#include <Windows.h>

namespace cyp
{
	namespace hardware
	{
		class Monitor
		{
		private:
			DISPLAY_DEVICE displayDevice;
			DEVMODE devmode;

		public:
			struct Info
			{
			public:
				std::string monitorName = "";		// The monitor name may be incorrect.
				unsigned long bitsPerPel = 0;		// how many bits of color the monitor can display.
				unsigned long pelsWidth = 0;		// monitor width
				unsigned long pelsHeight = 0;		// monitor height
				unsigned long displayFlags = 0;		// 0 : non grayScale & progressive,
													// 1 : grayScale, 2 : interlaced, 
													// 3 : grayScale & interlaced
				
				unsigned long displayFrequency = 0; // monitor fresh rate
				long position_x = 0;				// monitor x axis position (start point)
				long position_y = 0;				// monitor y axis position (start point)
			};

		public:
			std::vector<Info> v_info;

		public:
			Monitor();
			~Monitor();

			std::vector<Info> GetDisplayInfo();
		};
	}
}
