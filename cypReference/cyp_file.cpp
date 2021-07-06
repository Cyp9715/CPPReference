#include "cyp_file.hpp"

namespace cyp
{
	namespace file
	{
		bool deleteFile(const std::string& filePath)
		{
			return std::filesystem::remove(filePath) ? true : false;
		}

		bool createDirectory(const std::string& directoryLoc)
		{
			return std::filesystem::create_directory(directoryLoc) ? true : false;
		}

		void createFile(const std::string& filePath, const std::string& fileContent)
		{
			std::ofstream file(filePath);
			file << fileContent;
			file.close();
		}

		std::string readAllFile(const std::string& fileLoc)
		{
			std::ifstream file(fileLoc);
			std::string buffer = "";

			if (file.is_open()) {
				file.seekg(0, std::ios::end);
				int size = static_cast<int>(file.tellg());
				buffer.resize(size);
				file.seekg(0, std::ios::beg);
				file.read(&buffer[0], size);
				return buffer;
			}

			throw "error : cypReference::file::readAllFile";
		}
	}
}