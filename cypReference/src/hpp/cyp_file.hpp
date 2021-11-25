#pragma once
#include <filesystem>
#include <ostream>
#include <fstream>
#include <type_traits>
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
		class FileCommunication : cyp::communication::Tcp
		{
			u_short const HEADER_MAX = 20;
			u_short const HEADER_IDENT_MAX = 4;
			u_short const PAYLOAD_MAX = 3980;
			u_short const PACKET_MAX = 4000;
			char* HEADER_IDENT = new char[HEADER_IDENT_MAX] { 0x3D, 0x3D, 0x3D, 0x11 };

			cyp::hash::Sha sha;

			// send
			template<typename T>
			void extendArray(char* input, T addChar, int index, int insert_length);
			void assembleIngPacket();
			void assembleRemainPacket();

			char* s_header = new char[HEADER_MAX] { 0x3D, 0x3D, 0x3D, 0x11 };
			char* s_payload;
			char* s_Buffer = new char[PACKET_MAX];

			unsigned long long s_fileFullLength;
			unsigned long long s_fileIngLength;
			unsigned short s_fileRemainLength;

			// receive
			char* r_ident = new char[HEADER_IDENT_MAX];
			unsigned long long r_fileIngLength;
			unsigned long long r_fileFullLength;
			unsigned short r_fileRemainLength;
			char* r_payload;

			template<typename T>
			void assignCharArrToObject(T& obj, char* charArr);
			template<typename T, typename F>
			bool cmpObjectArr(T input1, F input2, int size);

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