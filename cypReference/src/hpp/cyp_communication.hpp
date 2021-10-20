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

			std::string receiveServer();
			std::string receiveClient();
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

			void open_send(const std::string& ip, const u_short port);
			void open_receive(const u_short port);

			bool send(const std::string& message);
			std::string receive();
		};


		class Udp_multicast
		{
		private:
			WSADATA _wsaData;
			struct ip_mreq _imr_receive;

			SOCKET _sendSocket = INVALID_SOCKET;
			SOCKET _recvSocket = INVALID_SOCKET;

			sockaddr_in _recvAddr = { 0 };
			sockaddr_in _sendAddr = { 0 };

			int _setsockoptBuf = 1;

		public:
			Udp_multicast();
			~Udp_multicast();

			void open_send(const std::string& multicastIp, const u_short port);
			void open_receive(const std::string& ip_multicast, const u_short port_multicast);

			bool send(const std::string& message);
			std::string receive();
		};

	}
};