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
			WSADATA _wsaData;

			SOCKET _listenSocket = INVALID_SOCKET;
			SOCKET _serverSocket = INVALID_SOCKET;
			SOCKET _clientSocket = INVALID_SOCKET;

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
			WSADATA _wsaData;

			SOCKET _sendSocket = INVALID_SOCKET;
			SOCKET _recvSocket = INVALID_SOCKET;

			sockaddr_in _recvAddr = { 0 };
			sockaddr_in _sendAddr = { 0 };
			sockaddr_in _dummyAddr = { 0 };
			int _dummyAddrSize = 0;

		public:
			Udp();
			~Udp();

			void open(const std::string& ip, const u_short port);

			bool send(const std::string& message);
			std::string receive();
		};
	}
};