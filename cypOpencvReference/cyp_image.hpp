#pragma once

#include "cyp_common.hpp"

namespace cyp
{
	class Image
	{
	private:
		bool CheckExistFile(const std::string& filePath);

	public:
		void ShowImg(std::string& title, std::string& filePath, cv::ImreadModes imreadModes = cv::IMREAD_COLOR);
		void ReadImage(std::string& filePath, cv::Mat& mat);
		void WriteImage(cv::Mat& mat, std::string& filePath);
	};
}