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
		void FileCommunication::extendArray(char* original, T addChar, int originalIndex, int addCharLength)
		{
			if constexpr (std::is_same_v<T, char*>)
			{
				memcpy(original + originalIndex, addChar, addCharLength);
			}
			else
			{
				memcpy(original + originalIndex, static_cast<char*>(static_cast<void*>(&addChar)), addCharLength);
			}
		}

		void FileCommunication::assembleIngPacket()
		{
			extendArray(s_header, s_fileIngLength, HEADER_IDENT_MAX, sizeof(unsigned long long));
			extendArray(s_Buffer, s_header, 0, HEADER_MAX);
			extendArray(s_Buffer, s_payload, HEADER_MAX, PAYLOAD_MAX);
			sha.strToSha<CryptoPP::SHA1>(s_Buffer).copy(s_checkSum, CHECKSUM_MAX);
			extendArray(s_Buffer, s_checkSum, PAYLOAD_MAX, HEADER_MAX);
		}

		void FileCommunication::assembleRemainPacket()
		{
			extendArray(s_header, s_fileRemainLength, HEADER_IDENT_MAX, sizeof(unsigned long long));
			extendArray(s_Buffer, s_header, 0, HEADER_MAX);
			extendArray(s_Buffer, s_payload, HEADER_MAX, PAYLOAD_MAX);
			sha.strToSha<CryptoPP::SHA1>(s_Buffer).copy(s_checkSum, CHECKSUM_MAX);
			extendArray(s_Buffer, s_checkSum, PAYLOAD_MAX, HEADER_MAX);
		}

		template<typename T, typename F>
		bool FileCommunication::cmpObjectArr(T input1, F input2, int size)
		{
			for (int iter_ = 0; iter_ < size; ++iter_)
			{
				if (input1[iter_] != input2[iter_])
				{
					return false;
				}
			}

			return true;
		}


		template<typename T>
		void FileCommunication::assignCharArrToObject(T& obj, char* charArr)
		{
			int size = sizeof(T);

			for (int iter_ = 0; iter_ < size; ++iter_)
			{
				obj[iter_] = charArr[iter_];
			}
		}


		FileCommunication::~FileCommunication()
		{
			delete[] s_header;
			delete[] s_checkSum;
			delete[] HEADER_IDENT;
			delete[] r_ident;
			delete[] r_checkSumContent;
		}

		/*
		* TCP basically guarantees sequential transmission.
		* However, the size is limited to 4 gb, and memory consumption may temporarily surge, 
		* So the file is disassembled and sent.
		* 
		* This process allows users to transfer up to 18446.744 Petabytes.
		* 
		* packet struct [8byte : default UDP Header], [20byte (4byte : identification number), (8byte : ingLength), (8byte : fullLength)]
		*				[1452byte : payload(disassemble body)], [20byte : sha1 checksum] = 1500 byte
		* 
		* I don't think it's a problem to use sha 1 because sha 1 is for simple error check, not security.
		*/
		void FileCommunication::sendFile(const std::string& ip, u_short port, const std::string& filePath)
		{
			open_send(ip, port);

			std::ifstream file(filePath, std::ios_base::binary);

			if (file.is_open())
			{
				file.seekg(0, std::ios::end);
				s_fileFullLength = file.tellg();
				file.seekg(0, std::ios::beg);

				extendArray(s_header, s_fileFullLength, 12, sizeof(unsigned long long));

				while (s_fileIngLength < s_fileFullLength)
				{
					s_payload = new char[PAYLOAD_MAX];
					file.read(s_payload, PAYLOAD_MAX);
					
					assembleIngPacket();

					if (sendto(_sendSocket, s_Buffer, static_cast<int>(PACKET_MAX), 0,
						(struct sockaddr*)&_recvAddr, sizeof(_recvAddr)) == SOCKET_ERROR)
					{
						throw "error : client error send";
					}
					
					Sleep(50); // testCode
					s_fileIngLength += PAYLOAD_MAX;

					delete[] s_payload;
				}

				s_fileRemainLength = s_fileFullLength - s_fileIngLength;

				s_payload = new char[s_fileRemainLength];
				file.read(s_payload, s_fileRemainLength);

				assembleRemainPacket();

				if (sendto(_sendSocket, s_Buffer, static_cast<int>(s_fileRemainLength), 0,
					(struct sockaddr*)&_recvAddr, sizeof(_recvAddr)) == SOCKET_ERROR)
				{
					throw "error : client error send";
				}

				delete[] s_payload;
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

			char* receiveBuffer = new char[PACKET_MAX];
			int ing = 0;

			std::ofstream file(filePath, std::ios::binary);
			int addrlen = sizeof(_recvAddr);

			while (true)
			{
				recvfrom(_recvSocket, receiveBuffer, PACKET_MAX, 0, (struct sockaddr*)&_recvAddr, &addrlen);
				memcpy(r_ident, receiveBuffer, HEADER_IDENT_MAX);

				if (cmpObjectArr(r_ident, HEADER_IDENT, HEADER_IDENT_MAX))
				{
					memcpy(&r_fileIngLength, receiveBuffer + 4, 8);
					memcpy(&r_fileFullLength, receiveBuffer + 12, 8);
					memcpy(r_checkSumContent, receiveBuffer, 1452 + 20);

					r_checkSum = sha.strToSha<CryptoPP::SHA1>(r_checkSumContent);

					if (cmpObjectArr(r_checkSumContent, r_checkSum, 1452 + 20))
					{
						memcpy(r_payload, receiveBuffer + HEADER_MAX, PAYLOAD_MAX);
						file.write(r_payload, PAYLOAD_MAX);
					}
					else
					{

					}
				}
			}

			delete[] receiveBuffer;

			closesocket(_recvSocket);
			WSACleanup();
		}
	}
}