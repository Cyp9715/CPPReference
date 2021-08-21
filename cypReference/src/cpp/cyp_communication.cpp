#include "cyp_communication.hpp"

namespace cyp
{
	namespace communication
	{
		Tcp::Tcp()
		{
			if (WSAStartup(MAKEWORD(2, 2), &_wsaData) != NO_ERROR)
			{
				throw "error : WSAStartup failed";
			}
		}

		Tcp::~Tcp()
		{
			closesocket(_listenSocket);
			closesocket(_serverSocket);
			closesocket(_clientSocket);

			WSACleanup();
		}

		void Tcp::openServer(const u_short port)
		{
			_listenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

			if (_listenSocket == INVALID_SOCKET)
			{
				throw "error : _listenSocket stop";
			}

			SOCKADDR_IN addrServer, addrClient;
			ZeroMemory(&addrServer, sizeof(addrServer));
			ZeroMemory(&addrClient, sizeof(addrClient));
			int addrSize = sizeof(addrClient);

			addrServer.sin_family = AF_INET;
			addrServer.sin_port = htons(port);
			addrServer.sin_addr.s_addr = htonl(INADDR_ANY);

			if (bind(_listenSocket, (SOCKADDR*)&addrServer, sizeof(addrServer)) == BIND_ERROR)
			{
				throw "error bind failed";
			}

			if (listen(_listenSocket, SOMAXCONN) == SOCKET_ERROR)
			{
				throw "error : listen failed";
			}

			_serverSocket = accept(_listenSocket, (SOCKADDR*)&addrClient, &addrSize);

			if (_serverSocket == INVALID_SOCKET)
			{
				throw "error : accept failed";
			}

			closesocket(_listenSocket);
		}

		void Tcp::openClient(const std::string& serverIp, const u_short port)
		{
			_clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

			if (socket(PF_INET, SOCK_STREAM, IPPROTO_TCP) == INVALID_SOCKET)
			{
				throw "error : _clientSocket stop";
			}

			SOCKADDR_IN addrServer;
			ZeroMemory(&addrServer, sizeof(addrServer));

			addrServer.sin_family = PF_INET;
			addrServer.sin_port = htons(port);
			if (inet_pton(PF_INET, serverIp.data(), &(addrServer.sin_addr.s_addr)) != INET_PTON_SUCCESS)
			{
				throw "error : can't inet_pton init";
			}

			if (connect(_clientSocket, (SOCKADDR*)&addrServer, sizeof(addrServer)) != 0)
			{
				throw "error : can't connection";
			}
		}

		std::string Tcp::receiveServer()
		{
			char buffer[512];

			if (recv(_serverSocket, buffer, 512, 0) == SOCKET_ERROR)
			{
				throw "error : accept failed";
			}

			return buffer;
		}

		std::string Tcp::receiveClient()
		{
			char buffer[512];

			if (recv(_clientSocket, buffer, 512, 0) == SOCKET_ERROR)
			{
				throw "error : accept failed";
			}

			return buffer;
		}

		void Tcp::sendServerToClient(const std::string& message)
		{
			if (send(_serverSocket, message.data(), static_cast<int>(message.length()), 0) == SOCKET_ERROR)
			{
				throw "error : server error send";
			}
		}

		void Tcp::sendClientToServer(const std::string& message)
		{
			if (send(_clientSocket, message.data(), static_cast<int>(message.length()), 0) == SOCKET_ERROR)
			{
				throw "error : client error send";
			}
		}


		Udp::Udp()
		{
			if (WSAStartup(MAKEWORD(2, 2), &_wsaData) != NO_ERROR)
			{
				throw "error : WSAStartup failed";
			}
		}

		Udp::~Udp()
		{
			closesocket(_sendSocket);
			closesocket(_recvSocket);

			WSACleanup();
		}

		void Udp::open(const std::string& ip, const u_short port)
		{
			_sendSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
			_recvSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

			ZeroMemory(&_dummyAddr, sizeof(_dummyAddr));
			ZeroMemory(&_recvAddr, sizeof(_recvAddr));
			ZeroMemory(&_sendAddr, sizeof(_sendAddr));
			_dummyAddrSize = sizeof(_dummyAddr);

			// recv
			_sendAddr.sin_family = PF_INET;
			_sendAddr.sin_port = htons(port);
			_sendAddr.sin_addr.s_addr = htonl(INADDR_ANY);

			// send
			_recvAddr.sin_family = PF_INET;
			_recvAddr.sin_port = htons(port);
			if (inet_pton(PF_INET, ip.data(), &_recvAddr.sin_addr.s_addr) != INET_PTON_SUCCESS)
			{
				throw "error : can't inet_pton init";
			}

			if (bind(_recvSocket, (SOCKADDR*)&_sendAddr, sizeof(_sendAddr)) == BIND_ERROR)
			{
				throw "error : bind failed";
			}
		}

		bool Udp::send(const std::string& message)
		{
			if (sendto(_sendSocket, message.data(), static_cast<int>(message.length()), 0,
				(struct sockaddr*)&_recvAddr, sizeof(_recvAddr)) == SOCKET_ERROR)
			{
				return false;
			}
			else
			{
				return true;
			}
		}

		std::string Udp::receive()
		{
			char buffer[512];
			recvfrom(_recvSocket, buffer, 512, 0, (SOCKADDR*)&_dummyAddr, &_dummyAddrSize);
			return buffer;
		}
	}

}