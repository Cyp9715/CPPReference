#pragma once
#include <filesystem>
#include <ostream>
#include <fstream>
#include <type_traits>
#include <typeinfo>
#include "cyp_communication.hpp"
#include "cyp_hash.hpp"

namespace cyp
{
	namespace file
	{
		void createFile(const std::string& filePath, const std::string& fileContent = "");
		bool deleteFile(const std::string& filePath);
		bool createDirectory(const std::string& directoryLoc);
		std::string readAllFile(const std::string& fileLoc);

		/* 
		* 1. Since the files are loaded into memory at onceand then transferred, a different solution is required for very large files.
		* 2. Basically, it operates within different PCs.
		* 3. There is room for improvement. (Especially in the receiving part.)
		* 
		* I'm going to correct the above problems and delete the comments within a few months.
		*/
		class FileCommunication : cyp::communication::Udp
		{
			char* header = new char[20] { 0x3D, 0x3D, 0x3D, 0x11 };
			char* payload;
			char* checkHash = new char[16];
			char* sendBuffer = new char[1500];

			template<typename T>
			void arrayAddarray_char(char* input, T addChar, int index, int insert_length);

			unsigned long long fileLength;
			unsigned long long ingLength;

			cyp::hash::Sha sha;

		public:
			~FileCommunication();

			// send : use tcp client.
			void sendFile(const std::string& ip, u_short port, const std::string& filePath);

			// receive : use tcp server
			// -> There is a possibility of improvement.
			void receiveFile(u_short port, std::string filePath, unsigned int fileByteSize);
		};
	}
}