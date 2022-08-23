#include "cyp_image.hpp"
#include <filesystem>

namespace cyp
{
	bool Image::CheckExistFile(const std::string& filePath)
	{
		std::filesystem::path p(filePath);
		return std::filesystem::exists(p) ? true : false;
	}

	void Image::ShowImg(std::string& title, std::string& filePath, cv::ImreadModes imreadModes)
	{
		std::string fileName = filePath;
		if (CheckExistFile(fileName))
		{
			cv::Mat mat = cv::imread(filePath, imreadModes);
			cv::imshow(title, mat);
			// need Wait
		}
		else
		{
			throw std::exception("file not exist");
		}
	}

	void Image::ReadImage(std::string& filePath, cv::Mat& mat)
	{
		mat = cv::imread(filePath);
	}


	void Image::WriteImage(cv::Mat& mat, std::string& filePath)
	{
		cv::imwrite(filePath, mat);
	}
}
