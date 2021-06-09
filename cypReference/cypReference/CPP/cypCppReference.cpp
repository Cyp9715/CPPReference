#include "cypCppReference.h"
#pragma warning(disable : 4996)

namespace cyp
{
	namespace string
	{
		bool isContain(const std::string& input_, const std::string& find_)
		{
			if (input_.find(find_) == std::string::npos)
			{
				return false;
			}
			else
			{
				return true;
			}
		}

		void changeStr(std::string& str_, const std::string& find_, const std::string& change)
		{
			size_t ui_num = str_.find(find_);

			while (true)
			{
				if (ui_num == std::string::npos)
				{
					return;
				}
				else
				{
					str_.erase(ui_num, find_.size());
					str_.insert(ui_num, change);
				}
				ui_num = str_.find(find_, change.size());
			}
		}

		bool isAlphabet(const std::string& str_)
		{
			for (size_t i = 0; i < str_.size(); ++i)
			{
				if ((str_[i] >= 97 && 122 >= str_[i]) || (str_[i] >= 65 && 90 >= str_[i]))
				{
					continue;
				}
				else
				{
					return false;
				}
			}
			return true;
		}

		bool isNumber(const std::string& str_)
		{
			return !str_.empty() && std::find_if(str_.begin(), str_.end(),
				[](unsigned char c) { return !std::isdigit(c); }) == str_.end();
		}

	}

	namespace vector
	{
		template<typename T>
		bool isContain(const std::vector<T>& v_input, const T find_)
		{
			if (std::find(v_input.begin(), v_input.end(), find_) != v_input.end())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	namespace file
	{
		bool deleteFile(const std::string& fileLoc_)
		{
			return std::filesystem::remove(fileLoc_) ? true : false;
		}

		bool createDirectory(const std::string& directoryLoc_)
		{
			return std::filesystem::create_directory(directoryLoc_) ? true : false;
		}

		void createFile(const std::string& fileLoc_, const std::string& fileContent_)
		{
			std::ofstream file(fileLoc_);
			file << fileContent_;
			file.close();
		}

		std::string readAllFile(const std::string& fileLoc_)
		{
			std::ifstream file(fileLoc_);
			std::string buffer = "";

			if (file.is_open()) {
				file.seekg(0, std::ios::end);
				int size = static_cast<int>(file.tellg());
				buffer.resize(size);
				file.seekg(0, std::ios::beg);
				file.read(&buffer[0], size);
				return buffer;
			}

			throw "error : cypReference::file::readAllFile";
		}
	}

	namespace communication
	{
		tcp::tcp()
		{
			if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
			{
				throw "error : WSAStartup failed";
			}

			listenSocket = INVALID_SOCKET;
			serverSocket = INVALID_SOCKET;
			clientSocket = INVALID_SOCKET;
		}

		tcp::~tcp()
		{
			closesocket(listenSocket);
			closesocket(serverSocket);
			closesocket(clientSocket);

			WSACleanup();
		}

		void tcp::openServer(const int port_)
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
			addrServer.sin_port = htons(port_);
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

		void tcp::openClient(const std::string& serverIp_, const int port_)
		{
			clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

			if (socket(PF_INET, SOCK_STREAM, IPPROTO_TCP) == INVALID_SOCKET)
			{
				throw "error : clientSocket stop";
			}

			SOCKADDR_IN addrServer;
			ZeroMemory(&addrServer, sizeof(addrServer));

			addrServer.sin_family = PF_INET;
			addrServer.sin_port = htons(port_);
			if (inet_pton(PF_INET, serverIp_.data(), &(addrServer.sin_addr.s_addr)) != INET_PTON_SUCCESS)
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

		void tcp::sendServerToClient(const std::string& message_)
		{
			if (send(serverSocket, message_.data(), static_cast<int>(message_.length()), 0) == SOCKET_ERROR)
			{
				throw "error : server error send";
			}			
		}

		void tcp::sendClientToServer(const std::string& message_)
		{
			if (send(clientSocket, message_.data(), static_cast<int>(message_.length()), 0) == SOCKET_ERROR)
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

		void udp::open(const std::string& ip_, const int port_)
		{
			sendSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
			recvSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

			ZeroMemory(&dummyAddr, sizeof(dummyAddr));
			ZeroMemory(&recvAddr, sizeof(recvAddr));
			ZeroMemory(&sendAddr, sizeof(sendAddr));
			dummyAddrSize = sizeof(dummyAddr);

			// recv
			sendAddr.sin_family = PF_INET;
			sendAddr.sin_port = htons(port_);
			sendAddr.sin_addr.s_addr = htonl(INADDR_ANY);
			
			// send
			recvAddr.sin_family = PF_INET;
			recvAddr.sin_port = htons(port_);
			if (inet_pton(PF_INET, ip_.data(), &recvAddr.sin_addr.s_addr) != INET_PTON_SUCCESS)
			{
				throw "error : can't inet_pton init";
			}

			if(bind(recvSocket, (SOCKADDR*)&sendAddr, sizeof(sendAddr)) == BIND_ERROR)
			{
				throw "error : bind failed";
			}
		}

		bool udp::send(const std::string& message_)
		{
			if (sendto(sendSocket, message_.data(), static_cast<int>(message_.length()), 0, 
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