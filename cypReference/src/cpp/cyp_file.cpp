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

		void FileCommunication::assignSendBuffer()
		{
			std::ifstream infile(sendFilePath);

			//get length of file
			infile.seekg(0, std::ios::end);
			size_t length = infile.tellg();
			infile.seekg(0, std::ios::beg);
			sendBuffer = new char[length];

			//read file
			infile.read(sendBuffer, length);
		}

		void FileCommunication::sendFile(const std::string& ip, u_short port, const std::string& filePath)
		{
			sendFilePath = filePath;
			openClient(ip, port);
			assignSendBuffer();
			sendClientToServer(sendBuffer);

			delete[] sendBuffer;
		}

		void FileCommunication::receiveFile(u_short port, std::string filePath)
		{
			openServer(port);
			const char * receiveBuffer = receiveServer().c_str();

			std::ofstream file(filePath, std::ios::binary);
			file.write(receiveBuffer, strlen(receiveBuffer));
		}
	}
}