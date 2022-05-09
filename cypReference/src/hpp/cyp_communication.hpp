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
		protected:
			WSADATA _wsaData;

			SOCKET _listenSocket = INVALID_SOCKET;
			SOCKET _serverSocket = INVALID_SOCKET;
			SOCKET _clientSocket = INVALID_SOCKET;

		public:
			Tcp();
			~Tcp();

			void OpenServer(const u_short port);
			void OpenClient(const std::string& serverIp, const u_short port);

			void SendServerToClient(const std::string& message);
			void SendClientToServer(const std::string& message);

			std::string ReceiveServer();
			std::string ReceiveClient();
		};

		class Udp
		{
		protected:
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

			void Open_send(const std::string& ip, const u_short port);
			void Open_receive(const u_short port);

			bool Send(const std::string& message);
			std::string Receive();
		};


		class Udp_multicast
		{
		protected:
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

			void Open_send(const std::string& multicastIp, const u_short port);
			void Open_receive(const std::string& ip_multicast, const u_short port_multicast);

			bool Send(const std::string& message);
			std::string Receive();
		};

	}
};