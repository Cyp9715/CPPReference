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

		void FileCommunication::FileSend::setHeader(unsigned long long ingCount, unsigned long long fullCount)
		{
			memcpy(header + 4, &ingCount, 8);
			memcpy(header + 12, &fullCount, 8);
		}

		void FileCommunication::FileSend::sendBuffer()
		{
			memcpy(buffer, header, 20);
			memcpy(buffer + 20, payload, 1440);

			if (send(_clientSocket, buffer, static_cast<int>(1460), 0) == SOCKET_ERROR)
			{
				throw "error : client error Send";
			}
		}

		void FileCommunication::FileSend::setEnd()
		{
			memset(&end[5], 1, 0x7F);
		}

		void FileCommunication::FileSend::fileHashCalculate(std::string filePath)
		{
			hex.StrToHex(sha.FileToSha<CryptoPP::SHA1>(filePath));
		}

		void FileCommunication::FileSend::sendFile(const std::string& ip, u_short port, const std::string& filePath)
		{
			fileHashCalculate(filePath);
			OpenClient(ip, port);

			std::ifstream file(filePath, std::ios::binary);

			if (file.is_open())
			{
				file.seekg(0, std::ios::end);
				unsigned long long fileLength = file.tellg();
				file.seekg(0, std::ios::beg);

				unsigned long long fullCount = fileLength / 1440;
				unsigned long long ingCount = 0;
				unsigned short remain = 0;

				while (ingCount < fullCount)
				{
					file.read(payload, 1440);
					file.seekg(1440, std::ios_base::cur);

					setHeader(ingCount, fullCount);
					sendBuffer();

					++ingCount;
					delete[] payload;
				}

				remain = static_cast<unsigned short>(fileLength - (1480 * ingCount));

				payload = new char[remain];
				file.read(payload, remain);
				file.seekg(remain, std::ios_base::cur);

				if (send(_clientSocket, payload, static_cast<int>(remain), 0) == SOCKET_ERROR)
				{
					throw "error : client error Send";
				}

				delete[] payload;
			}
			else
			{
				throw "error : Unable to open file.";
			}

			closesocket(_clientSocket);
		}

		void FileCommunication::FileReceive::receiveFile(u_short port, std::string filePath, unsigned int fileByteSize)
		{
			OpenServer(port);

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



		FileCommunication::FileSend::FileSend()
		{
			memcpy(header, identifier, 4);
			memcpy(end, identifier, 4);
		}
	}
}