#pragma once
#include <filesystem>
#include <ostream>
#include <fstream>
#include "cyp_communication.hpp"

namespace cyp
{
	namespace file
	{
		void createFile(const std::string& filePath, const std::string& fileContent = "");
		bool deleteFile(const std::string& filePath);
		bool createDirectory(const std::string& directoryLoc);
		std::string readAllFile(const std::string& fileLoc);

		/* 
		* Since the files are loaded into memory at onceand then transferred, a different solution is required for very large files.
		* ¡Ø currently looking for an encrypted file transfer method.
		*    the only known working file is a.txt file.
		*/
		class FileCommunication : cyp::communication::Tcp
		{
		private:
			//char* sendBuffer;
			std::string sendFilePath;
			std::string receiveFilePath;

			// send
			void readFileSend();
			
		public:
			// send : use tcp client.
			void sendFile(const std::string& ip, u_short port, const std::string& filePath);

			// receive : use tcp server
			void receiveFile(u_short port, std::string filePath);
		};
	}
}