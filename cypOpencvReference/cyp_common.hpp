#pragma once
#include <iostream>
#include <filesystem>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

static bool ExistFile_(const std::string& filePath)
{
	std::filesystem::path p(filePath);
	return std::filesystem::exists(p) ? true : false;
}