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


		void FileCommunication::readFileSend()
		{
			std::ifstream file(sendFilePath, std::ios::out | std::ios::binary);

			//get length of file
			file.seekg(0, std::ios::end);
			size_t length = file.tellg();
			file.seekg(0, std::ios::beg);
			char *sendBuffer = new char[length];
			file.read(sendBuffer, length);

			if (send(_clientSocket, sendBuffer, static_cast<int>(length), 0) == SOCKET_ERROR)
			{
				throw "error : client error send";
			}

			delete[] sendBuffer;
		}

		void FileCommunication::sendFile(const std::string& ip, u_short port, const std::string& filePath)
		{
			sendFilePath = filePath;
			openClient(ip, port);
			readFileSend();
		}

		void FileCommunication::receiveFile(u_short port, std::string filePath, unsigned int fileByteSize)
		{
			openServer(port);
			
			char* receiveBuffer = new char[fileByteSize];
			recv(_serverSocket, receiveBuffer, fileByteSize, 0);

			std::ofstream file(filePath, std::ios::binary);
			file.write(receiveBuffer, fileByteSize);
		}
	}
}