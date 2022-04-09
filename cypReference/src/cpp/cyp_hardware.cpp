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
			v_info.clear();
			Info info;

			int deviceIndex = 0;
			
			while (EnumDisplayDevices(NULL, deviceIndex++, &displayDevice, 0))
			{
				std::string deviceName = displayDevice.DeviceName;

				int monitorIndex = 0;

				while (EnumDisplayDevices(deviceName.c_str(), monitorIndex++, &displayDevice, 0))
				{
					EnumDisplaySettings(deviceName.c_str(), ENUM_REGISTRY_SETTINGS, &devmode);
					info.monitorName = displayDevice.DeviceString;
					info.dmBitsPerPel = devmode.dmBitsPerPel;
					info.dmPelsWidth = devmode.dmPelsWidth;
					info.dmPelsHeight = devmode.dmPelsHeight;
					info.dmDisplayFlags = devmode.dmDisplayFlags;
					info.dmDisplayFrequency = devmode.dmDisplayFrequency;

					v_info.push_back(info);
				}
			}

			return v_info;
		}
	}
}