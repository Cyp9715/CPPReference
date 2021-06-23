#pragma once

// string
#include <string>

// vector
#include <vector>

// file
#include <filesystem>
#include <ostream>
#include <fstream>

// communication
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32")

// hash
#include "cryptopp/cryptlib.h"
#include "cryptopp/channels.h"
#include "cryptopp/filters.h"
#include "cryptopp/files.h"
#include "cryptopp/sha.h"
#include "cryptopp/crc.h"
#include "cryptopp/hex.h"

namespace cyp
{
	namespace string
	{
		bool isAlphabet(const std::string& str);
		bool isContain(const std::string& original, const std::string& find);
		bool isNumber(const std::string& str);

		void changeStr(std::string& str, const std::string& find, const std::string& change);
		
		std::string removeExtension(const std::string& fileName, bool removeMultiExtension = false);
	};

	namespace vector
	{
		template<typename T>
		bool isContain(const std::vector<T>& v_input, const T find);
	};

	namespace file
	{
		void createFile(const std::string& filePath, const std::string& fileContent = "");
		bool deleteFile(const std::string& filePath);
		bool createDirectory(const std::string& directoryLoc);
		std::string readAllFile(const std::string& fileLoc);
	}

	namespace hash
	{
		std::string strToMD5(const std::string& str);
		std::string fileToMD5(const std::string filePath);
		std::string strToSHA256(const std::string& str);
		std::string fileToSHA256(const std::string& filePath);
		std::string strToSHA512(const std::string& str);
		std::string fileToSHA512(const std::string& filePath);
	}

	namespace communication
	{
		enum error
		{
			BIND_ERROR = -1,
			BIND_SUCCESS = 0,
			INET_PTON_SUCCESS = 1
		};

		class tcp
		{
		private:
			WSADATA wsaData;

			SOCKET listenSocket = INVALID_SOCKET;
			SOCKET serverSocket = INVALID_SOCKET;
			SOCKET clientSocket = INVALID_SOCKET;

		public:
			tcp();
			~tcp();

			void openServer(const u_short port);
			void openClient(const std::string& serverIp, const u_short port);

			void sendServerToClient(const std::string& message);
			void sendClientToServer(const std::string& message);

			std::string serverReceive();
			std::string clientReceive();
		};

		class udp
		{
		private:
			WSADATA wsaData;

			SOCKET sendSocket = INVALID_SOCKET;
			SOCKET recvSocket = INVALID_SOCKET;

			sockaddr_in recvAddr = { 0 };
			sockaddr_in sendAddr = { 0 };
			sockaddr_in dummyAddr = { 0 };
			int dummyAddrSize = 0;

		public:
			udp();
			~udp();

			void open(const std::string& ip, const u_short port);

			bool send(const std::string& message);
			std::string receive();
		};
	}
};