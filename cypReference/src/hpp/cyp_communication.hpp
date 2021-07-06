#pragma once
#include "cyp_common.hpp"

#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32")


namespace cyp
{
	namespace communication
	{
		enum error
		{
			BIND_ERROR = -1,
			BIND_SUCCESS = 0,
			INET_PTON_SUCCESS = 1
		};

		class Tcp
		{
		private:
			WSADATA wsaData;

			SOCKET listenSocket = INVALID_SOCKET;
			SOCKET serverSocket = INVALID_SOCKET;
			SOCKET clientSocket = INVALID_SOCKET;

		public:
			Tcp();
			~Tcp();

			void openServer(const u_short port);
			void openClient(const std::string& serverIp, const u_short port);

			void sendServerToClient(const std::string& message);
			void sendClientToServer(const std::string& message);

			std::string serverReceive();
			std::string clientReceive();
		};

		class Udp
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
			Udp();
			~Udp();

			void open(const std::string& ip, const u_short port);

			bool send(const std::string& message);
			std::string receive();
		};
	}
};