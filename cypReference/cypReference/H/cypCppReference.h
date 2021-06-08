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

namespace cyp
{
	namespace string
	{
		static bool isAlphabet(const std::string& str_);
		static bool isContain(const std::string& original, const std::string& find_);
		static void changeStr(std::string& str_, const std::string& find_, const std::string& change);
		static bool isNumber(const std::string& str_);
	};

	namespace vector
	{
		template<typename T>
		static bool isContain(const std::vector<T>& v_input, const T find_);
	};

	namespace file
	{
		static bool deleteFile(const std::string& fileLoc_);
		static bool createDirectory(const std::string& directoryLoc_);
		static void createFile(const std::string& fileName_, const std::string& fileContent_ = "");
		static std::string readAllFile(const std::string& fileName_);
	}

	// windows
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

			// using server
			SOCKET listenSocket;
			SOCKET clientSocket;

			// using client
			SOCKET serverSocket;

		public:
			tcp();
			~tcp();

			void openServer(const int port_);
			void openClient(const std::string& serverIp_, const int port_);

			void sendServerToClient(std::string& message_);
			void sendClientToServer(std::string& message_);

			std::string serverReceive();
			std::string clientReceive();
		};

		class udp
		{
			WSADATA wsaData;

			SOCKET sendSocket = INVALID_SOCKET;
			SOCKET recvSocket;

			sockaddr_in recvAddr, sendAddr, dummyAddr;
			int dummyAddrSize = 0;

		public:
			udp();
			~udp();

			void open(const std::string& ip_, const int port_);

			bool send(const std::string& message_);
			std::string receive();
		};
	}
};