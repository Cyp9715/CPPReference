#pragma once
#include <opencv2/highgui.hpp>

namespace cyp
{
	class ShowImage
	{
	public:
		ShowImage(std::string&& title, std::string&& filePath);
	};
}