#pragma once
#include <cyp_common.hpp>
#include <vector>
#include <Windows.h>

class Monitor
{
private:
	PDISPLAY_DEVICE displayDevice = new DISPLAY_DEVICE();
	PDEVMODEA devmode = new DEVMODEA();

public:
	struct Info
	{
	public:
		unsigned long dmBitsPerPel;
		unsigned long dmPelsWidth;
		unsigned long dmPelsHeight;
		unsigned long dmDisplayFlags;
		unsigned long dmDisplayFrequency;
	};

public:
	std::vector<Info> v_info;
	int loop = 0;

public:
	Monitor();
	~Monitor();

	std::vector<Info> GetDisplayInfo();
};