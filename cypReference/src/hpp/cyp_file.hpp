#pragma once
#include <filesystem>
#include <ostream>
#include <fstream>

namespace cyp
{
	namespace file
	{
		void createFile(const std::string& filePath, const std::string& fileContent = "");
		bool deleteFile(const std::string& filePath);
		bool createDirectory(const std::string& directoryLoc);
		std::string readAllFile(const std::string& fileLoc);
	}
}