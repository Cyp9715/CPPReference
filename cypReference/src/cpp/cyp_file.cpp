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

		void FileCommunication::sendFile(const std::string& ip, u_short port, const std::string& filePath)
		{
			openClient(ip, port);

			std::ifstream file(filePath, std::ios::out | std::ios::binary);

			if (file.is_open())
			{
				char* sendBuffer;
				file.seekg(0, std::ios::end);
				unsigned long long fileLength = file.tellg();
				file.seekg(0, std::ios::beg);

				unsigned long long loopCount = fileLength / 1480;
				unsigned long long ing = 0;

				while (ing < loopCount)
				{
					sendBuffer = new char[1480];
					ZeroMemory(sendBuffer, 1480);
					file.read(sendBuffer, 1480);
					file.seekg(1480);

					if(send(_clientSocket, sendBuffer, static_cast<int>(1480), 0))
					{
						throw "error : client error send";
					}
					
					std::cout << ing << std::endl;

					++ing;
					delete[] sendBuffer;
				}

				file.seekg(std::ios::end);
				unsigned short end = static_cast<unsigned short>(file.tellg());

				sendBuffer = new char[end];
				file.read(sendBuffer, end);

				if (send(_clientSocket, sendBuffer, static_cast<int>(end), 0) == SOCKET_ERROR)
				{
					throw "error : client error send";
				}

				delete[] sendBuffer;
			}
			else
			{
				throw "error : Unable to open file.";
			}

			closesocket(_clientSocket);
		}

		void FileCommunication::receiveFile(u_short port, std::string filePath, unsigned int fileByteSize)
		{
			openServer(port);
			
			char* receiveBuffer = new char[1480];
			int ing = 0;

			std::ofstream file(filePath, std::ios::binary);

			// testCode
			while (ing < 591)
			{
				recv(_serverSocket, receiveBuffer, 1480, 0);
				file.write(receiveBuffer, 1480);
				++ing;
			}

			delete[] receiveBuffer;

			receiveBuffer = new char[200];
			recv(_serverSocket, receiveBuffer, 200, 0);
			file.write(receiveBuffer, 200);

			delete[] receiveBuffer;
			
			closesocket(_listenSocket);
			closesocket(_serverSocket);
		}
	}
}