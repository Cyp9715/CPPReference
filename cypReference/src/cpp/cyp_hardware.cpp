#include "cyp_hardware.hpp"

namespace cyp
{
	namespace hardware
	{
		Monitor::Monitor()
		{
			displayDevice.cb = sizeof(displayDevice);
			devmode.dmSize = sizeof(devmode);
		}

		Monitor::~Monitor()
		{
		}

		std::vector<Monitor::Info> Monitor::GetDisplayInfo()
		{
			Info info;
			v_info.clear();

			int deviceIndex = 0;
			
			while (EnumDisplayDevices(NULL, deviceIndex++, &displayDevice, 0))
			{
				std::string deviceName = displayDevice.DeviceName;

				int monitorIndex = 0;

				while (EnumDisplayDevices(deviceName.c_str(), monitorIndex++, &displayDevice, 0))
				{
					EnumDisplaySettings(deviceName.c_str(), ENUM_REGISTRY_SETTINGS, &devmode);
					info.monitorName = displayDevice.DeviceString;
					info.bitsPerPel = devmode.dmBitsPerPel;
					info.pelsWidth = devmode.dmPelsWidth;
					info.pelsHeight = devmode.dmPelsHeight;
					info.displayFlags = devmode.dmDisplayFlags;
					info.displayFrequency = devmode.dmDisplayFrequency;
					info.position_x = devmode.dmPosition.x;
					info.position_y = devmode.dmPosition.y;

					v_info.push_back(info);
				}
			}
			
			return v_info;
		}
	}
}