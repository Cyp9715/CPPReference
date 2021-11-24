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

		template<typename T>
		void FileCommunication::arrayAddarray_char(char* original, T addChar, int originalIndex, int addCharLength)
		{
			std::cout << typeid(addChar).name() << std::endl;
			if constexpr (std::is_same_v<T, char*>)
			{
				memcpy(original + originalIndex, addChar, addCharLength);
			}
			else
			{
				memcpy(original + originalIndex, static_cast<char*>(static_cast<void*>(&addChar)), addCharLength);
			}
		}

		FileCommunication::~FileCommunication()
		{
			delete[] header;
			delete[] checkHash;
		}

		/*
		* TCP basically guarantees sequential transmission.
		* However, the size is limited to 4 gb, and memory consumption may temporarily surge, 
		* So the file is disassembled and sent.
		* 
		* This process allows users to transfer up to 18446.744 Petabytes.
		*/
		void FileCommunication::sendFile(const std::string& ip, u_short port, const std::string& filePath)
		{
			open_send(ip, port);

			std::ifstream file(filePath, std::ios_base::binary);

			if (file.is_open())
			{
				file.seekg(0, std::ios::end);
				fileLength = file.tellg();
				file.seekg(0, std::ios::beg);

				// byte Count
				unsigned short remainCount = 0;
				
				arrayAddarray_char(header, fileLength, 4, sizeof(unsigned long long));

				while (ingLength < fileLength)
				{
					payload = new char[1456];
					file.read(payload, 1456);
					
					arrayAddarray_char(header, ingLength, 12, sizeof(unsigned long long));
					arrayAddarray_char(sendBuffer, header, 0, 20);
					arrayAddarray_char(sendBuffer, payload, 20, 1456);
					sha.strToSha<CryptoPP::SHA1>(sendBuffer);

					if (sendto(_sendSocket, sendBuffer, static_cast<int>(1500), 0,
						(struct sockaddr*)&_recvAddr, sizeof(_recvAddr)) == SOCKET_ERROR)
					{
						throw "error : client error send";
					}
					
					Sleep(50);
					ingLength += 1456;

					delete[] payload;
				}

				remainCount = fileLength - ingLength;

				payload = new char[remainCount];
				file.read(payload, remainCount);

				if (sendto(_sendSocket, sendBuffer, static_cast<int>(remainCount), 0,
					(struct sockaddr*)&_recvAddr, sizeof(_recvAddr)) == SOCKET_ERROR)
				{
					throw "error : client error send";
				}

				delete[] payload;
			}
			else
			{
				throw "error : Unable to open file.";
			}

			closesocket(_sendSocket);
			WSACleanup();
		}

		/* 
		* The reason for using std::vector is that it is sent in order when sending,
		* but there is no guarantee that it will come in order when receiving it. 
		*/
		void FileCommunication::receiveFile(u_short port, std::string filePath, unsigned int fileByteSize)
		{
			open_receive(port);

			char* receiveBuffer = new char[1480];
			int ing = 0;

			std::ofstream file(filePath, std::ios::binary);
			int addrlen = sizeof(_recvAddr);

			// testCode
			while (ing < 591)
			{
				recvfrom(_recvSocket, receiveBuffer, 1480, 0, (struct sockaddr*)&_recvAddr, &addrlen);
				file.write(receiveBuffer, 1480);
				++ing;
			}

			delete[] receiveBuffer;

			receiveBuffer = new char[200];
			recvfrom(_recvSocket, receiveBuffer, 200, 0, (struct sockaddr*)&_recvAddr, &addrlen);

			file.write(receiveBuffer, 200);

			delete[] receiveBuffer;

			closesocket(_recvSocket);
			WSACleanup();
		}
	}
}