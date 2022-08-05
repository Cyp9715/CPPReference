#pragma once
#include <filesystem>
#include <ostream>
#include <fstream>
#include "cyp_communication.hpp"
#include "cyp_hash.hpp"
#include "cyp_convert.hpp"

namespace cyp
{
	namespace file
	{
		bool ExistFile(const std::string& filePath);
		void CreateFile(const std::string& filePath, const std::string& fileContent = "");
		bool DeleteFile(const std::string& filePath);
		bool CreateDirectory(const std::string& directoryLoc);
		std::string ReadAllFile(const std::string& fileLoc);

		/*
		* 1. Since the files are loaded into memory at onceand then transferred, a different solution is required for very large files.
		* 2. Basically, it operates within different PCs.
		* 3. There is room for improvement. (Especially in the receiving part.)
		*
		* I'm going to correct the above problems and delete the comments within a few months.
		*/
		class FileCommunication
		{
		public:
			class FileSend : cyp::communication::Tcp
			{
				cyp::hash::Sha sha;
				cyp::convert::Hex hex;

				char* identifier = new char[4] { 0x00, 0x47, 0x02, 0x4F };
				char* init = new char[13];
				char* header = new char[20];
				char* payload = new char[1440];
				char* buffer = new char[1460];
				char* end = new char[25];

				unsigned char* fileHash = new unsigned char[20];

				void SetHeader(unsigned long long ingLength, unsigned long long fullLength);
				void SendBuffer();
				void setEnd();
				void FileHashCalculate(std::string filePath);

			public:
				// Send : use tcp client.
				FileSend();
				void SendFile(const std::string& ip, u_short port, const std::string& filePath);

				// Receive : use tcp server
				// -> There is a possibility of improvement.
			};

			class FileReceive : cyp::communication::Tcp
			{
				// Receive

			public:
				// Receive : use tcp server
				// -> There is a possibility of improvement.
				void ReceiveFile(u_short port, std::string filePath, unsigned int fileByteSize);
			};

		};
	}
}