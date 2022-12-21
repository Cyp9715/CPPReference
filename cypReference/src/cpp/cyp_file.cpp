#include "cyp_file.hpp"

namespace cyp
{
	namespace file
	{
		bool ExistFile(const std::string& filePath)
		{
			std::filesystem::path p(filePath);
			return std::filesystem::exists(p) ? true : false;
		}

		bool DeleteFile(const std::string& filePath)
		{
			return std::filesystem::remove(filePath) ? true : false;
		}

		bool CreateDirectory(const std::string& directoryLoc)
		{
			return std::filesystem::create_directory(directoryLoc) ? true : false;
		}

		void CreateFile(const std::string& filePath, const std::string& fileContent)
		{
			std::ofstream file(filePath);
			file << fileContent;
			file.close();
		}

		std::string ReadAllFile(const std::string& fileLoc)
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

		void FileCommunication::FileSend::SendHeader(SOCKET& sendSocket, Packet_FileHeader& packet_fileHeader)
		{
			if (send(sendSocket, reinterpret_cast<char*>(&packet_fileHeader), static_cast<int>(sizeof(Packet_FileHeader)), 0) == SOCKET_ERROR)
			{
				throw "error : client error Send";
			}
		}

		void FileCommunication::FileSend::SendBody(SOCKET& sendSocket, Packet_FileBody& packet_fileBody, unsigned int packetSize)
		{
			if (send(sendSocket, reinterpret_cast<char *>(packet_fileBody.buffer), packetSize, 0) == SOCKET_ERROR)
			{
				throw "error : client error Send";
			}
		}

		void FileCommunication::FileSend::SendFile(const u_short port, const std::string filePath)
		{
			SOCKET serverSocket = OpenServer(port);

			std::ifstream file(filePath, std::ios::binary);
			Packet_FileHeader fileHeader;
			Packet_FileBody fileBody;

			if (file.is_open())
			{
				file.seekg(0, std::ios::end);
				fileHeader.fileSize_byte = file.tellg();
				file.seekg(0, std::ios::beg);

				unsigned long long loopCount_full = fileHeader.fileSize_byte / MB2;
				unsigned long long loopCount_present = 0;
				unsigned int remainSize = static_cast<unsigned int>(fileHeader.fileSize_byte - (loopCount_full * MB2));

				SendHeader(serverSocket, fileHeader);

				if (fileHeader.fileSize_byte >= MB2)
				{
					fileBody.buffer = new char[MB2];

					// For memory limit, large files are sent in 2MB units 
					while (loopCount_present < loopCount_full)
					{
						file.read(fileBody.buffer, MB2);

						SendBody(serverSocket, fileBody, MB2);
						++loopCount_present;
					}

					delete[] fileBody.buffer;
				}
				
				fileBody.buffer = new char[remainSize];
				file.read(fileBody.buffer, remainSize);

				SendBody(serverSocket, fileBody, remainSize);

				delete[] fileBody.buffer;
			}
			else
			{
				throw "error : Unable to open file.";
			}
		}

		void FileCommunication::FileReceive::ReceiveFile(const std::string ip, const u_short port, const std::string filePath, double& progress)
		{
			SOCKET clientSocket = OpenClient(ip, port);

			Packet_FileHeader fileHeader;
			Packet_FileBody fileBody;
			char recvIdentifier[4] = { '\0', };

			memset(fileHeader.identifier, '\0', 4);
			recv(clientSocket, reinterpret_cast<char*>(&fileHeader), sizeof(Packet_FileHeader), 0);
			memcpy(recvIdentifier, fileHeader.identifier, 4);

			unsigned long long totalRecvSize = 0;

			// check Header.
			if (memcmp(fileHeader.identifier, recvIdentifier, 4) == 0)
			{
				fileBody.buffer = new char[MB2];
				std::ofstream file(filePath, std::ios::binary);

				int count = 0;

				if (file.is_open())
				{
					while (fileHeader.fileSize_byte > totalRecvSize)
					{
						int receiveSize = recv(clientSocket, reinterpret_cast<char*>(fileBody.buffer), MB2, 0);
						
						if (receiveSize <= 0)
						{
							if (receiveSize == 0)
							{
								throw "error : FileCommunication::FileReceive::ReceiveFile() shutdown FileSender";
							}
							else
							{
								throw "error : FileCommunication::FileReceive::ReceiveFile()";
							}

						}
						
						file.write(fileBody.buffer, receiveSize);
						totalRecvSize += receiveSize;
					
						progress = round((double)totalRecvSize / (double)fileHeader.fileSize_byte * 100000) / 1000;
					}
				}

				delete[] fileBody.buffer;
			}
		}
	}
}