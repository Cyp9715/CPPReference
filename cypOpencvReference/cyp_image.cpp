#include "cyp_image.hpp"

namespace cyp
{
	ShowImage::ShowImage(std::string&& title, std::string&& filePath)
	{
        cv::Mat mat = cv::imread(filePath, cv::IMREAD_COLOR);
		cv::imshow(title, mat);
		// need Wait
	}
}
