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
				std::string monitorName;	// The monitor name may be incorrect.
				unsigned long dmBitsPerPel;
				unsigned long dmPelsWidth;
				unsigned long dmPelsHeight;
				unsigned long dmDisplayFlags;
				unsigned long dmDisplayFrequency;
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
