#include "cyp_communication.hpp"

namespace cyp
{
	namespace communication
	{
		tcp::tcp()
		{
			if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
			{
				throw "error : WSAStartup failed";
			}
		}

		tcp::~tcp()
		{
			closesocket(listenSocket);
			closesocket(serverSocket);
			closesocket(clientSocket);

			WSACleanup();
		}

		void tcp::openServer(const u_short port)
		{
			listenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

			if (listenSocket == INVALID_SOCKET)
			{
				throw "error : listenSocket stop";
			}

			SOCKADDR_IN addrServer, addrClient;
			ZeroMemory(&addrServer, sizeof(addrServer));
			ZeroMemory(&addrClient, sizeof(addrClient));
			int addrSize = sizeof(addrClient);

			addrServer.sin_family = AF_INET;
			addrServer.sin_port = htons(port);
			addrServer.sin_addr.s_addr = htonl(INADDR_ANY);

			if (bind(listenSocket, (SOCKADDR*)&addrServer, sizeof(addrServer)) == BIND_ERROR)
			{
				throw "error bind failed";
			}

			if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
			{
				throw "error : listen failed";
			}

			serverSocket = accept(listenSocket, (SOCKADDR*)&addrClient, &addrSize);

			if (serverSocket == INVALID_SOCKET)
			{
				throw "error : accept failed";
			}

			closesocket(listenSocket);
		}

		void tcp::openClient(const std::string& serverIp, const u_short port)
		{
			clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

			if (socket(PF_INET, SOCK_STREAM, IPPROTO_TCP) == INVALID_SOCKET)
			{
				throw "error : clientSocket stop";
			}

			SOCKADDR_IN addrServer;
			ZeroMemory(&addrServer, sizeof(addrServer));

			addrServer.sin_family = PF_INET;
			addrServer.sin_port = htons(port);
			if (inet_pton(PF_INET, serverIp.data(), &(addrServer.sin_addr.s_addr)) != INET_PTON_SUCCESS)
			{
				throw "error : can't inet_pton init";
			}

			if (connect(clientSocket, (SOCKADDR*)&addrServer, sizeof(addrServer)) != 0)
			{
				throw "error : can't connection";
			}
		}

		std::string tcp::serverReceive()
		{
			char buffer[512];

			if (recv(serverSocket, buffer, 512, 0) == SOCKET_ERROR)
			{
				throw "error : accept failed";
			}

			return buffer;
		}

		std::string tcp::clientReceive()
		{
			char buffer[512];

			if (recv(clientSocket, buffer, 512, 0) == SOCKET_ERROR)
			{
				throw "error : accept failed";
			}

			return buffer;
		}

		void tcp::sendServerToClient(const std::string& message)
		{
			if (send(serverSocket, message.data(), static_cast<int>(message.length()), 0) == SOCKET_ERROR)
			{
				throw "error : server error send";
			}
		}

		void tcp::sendClientToServer(const std::string& message)
		{
			if (send(clientSocket, message.data(), static_cast<int>(message.length()), 0) == SOCKET_ERROR)
			{
				throw "error : client error send";
			}
		}


		udp::udp()
		{
			if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
			{
				throw "error : WSAStartup failed";
			}
		}

		udp::~udp()
		{
			closesocket(sendSocket);
			closesocket(recvSocket);

			WSACleanup();
		}

		void udp::open(const std::string& ip, const u_short port)
		{
			sendSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
			recvSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

			ZeroMemory(&dummyAddr, sizeof(dummyAddr));
			ZeroMemory(&recvAddr, sizeof(recvAddr));
			ZeroMemory(&sendAddr, sizeof(sendAddr));
			dummyAddrSize = sizeof(dummyAddr);

			// recv
			sendAddr.sin_family = PF_INET;
			sendAddr.sin_port = htons(port);
			sendAddr.sin_addr.s_addr = htonl(INADDR_ANY);

			// send
			recvAddr.sin_family = PF_INET;
			recvAddr.sin_port = htons(port);
			if (inet_pton(PF_INET, ip.data(), &recvAddr.sin_addr.s_addr) != INET_PTON_SUCCESS)
			{
				throw "error : can't inet_pton init";
			}

			if (bind(recvSocket, (SOCKADDR*)&sendAddr, sizeof(sendAddr)) == BIND_ERROR)
			{
				throw "error : bind failed";
			}
		}

		bool udp::send(const std::string& message)
		{
			if (sendto(sendSocket, message.data(), static_cast<int>(message.length()), 0,
				(struct sockaddr*)&recvAddr, sizeof(recvAddr)) == SOCKET_ERROR)
			{
				return false;
			}
			else
			{
				return true;
			}
		}

		std::string udp::receive()
		{
			char buffer[512];
			recvfrom(recvSocket, buffer, 512, 0, (SOCKADDR*)&dummyAddr, &dummyAddrSize);
			return buffer;
		}
	}

}