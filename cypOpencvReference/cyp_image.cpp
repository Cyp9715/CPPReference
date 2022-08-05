#include "cyp_image.hpp"
#include <filesystem>

namespace cyp
{
	ShowImage::ShowImage(std::string&& title, std::string&& filePath)
	{
		std::string fileName = filePath;
		if (ExistFile_(fileName))
		{
			cv::Mat mat = cv::imread(filePath, cv::IMREAD_COLOR);
			cv::imshow(title, mat);
			// need Wait
		}
		else
		{
			throw std::exception("file not exist");
		}
	}
}
