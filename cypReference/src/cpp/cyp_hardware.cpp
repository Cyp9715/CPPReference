#include "cyp_hardware.hpp"

Monitor::Monitor()
{
	displayDevice->cb = sizeof(DISPLAY_DEVICE);
}

Monitor::~Monitor()
{
	delete displayDevice;
	delete devmode;
}

std::vector<Monitor::Info> Monitor::GetDisplayInfo()
{
	v_info.clear();
	Info info;

	while (true)
	{
		if (EnumDisplayDevices(NULL, loop++, displayDevice, EDD_GET_DEVICE_INTERFACE_NAME) == false)
		{
			break;
		}

		EnumDisplaySettings(displayDevice->DeviceName, ENUM_REGISTRY_SETTINGS, devmode);

		if (devmode->dmBitsPerPel == 0)
		{
			break;
		}

		info.dmBitsPerPel = devmode->dmBitsPerPel;
		info.dmPelsWidth = devmode->dmPelsWidth;
		info.dmPelsHeight = devmode->dmPelsHeight;
		info.dmDisplayFlags = devmode->dmDisplayFlags;
		info.dmDisplayFrequency = devmode->dmDisplayFrequency;

		v_info.push_back(info);
	}

	return v_info;
}