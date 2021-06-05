#include "cypCppReference.h"

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

		void createFile(const std::string& fileName_, const std::string& fileContent_)
		{
			std::ofstream file(fileName_);
			file << fileContent_;
			file.close();
		}

		std::string readAllFile(const std::string& fileName_)
		{
			std::ifstream file(fileName_);
			std::string buffer = "";

			if (file.is_open()) {
				file.seekg(0, std::ios::end);
				int size = static_cast<int>(file.tellg());
				buffer.resize(size);
				file.seekg(0, std::ios::beg);
				file.read(&buffer[0], size);
				return buffer;
			}

			return "error : cypReference::file::readAllFile";
		}
	}

	namespace communication
	{
		tcp::tcp()
		{
			if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
			{
				throw "error : WSAStartup failed";
			}
		}

		tcp::~tcp()
		{
			WSACleanup();
		}

		void tcp::openServer(const int port_)
		{
			*socListen = INVALID_SOCKET;
			*socClient = INVALID_SOCKET;

			*socListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

			if (*socListen == INVALID_SOCKET)
			{
				WSACleanup();
				throw "error : listenSocket stop";
			}

			SOCKADDR_IN addrServer;
			addrServer.sin_family = AF_INET;
			addrServer.sin_port = htons(port_);
			addrServer.sin_addr.s_addr = htonl(INADDR_ANY);

			if (bind(*socListen, (SOCKADDR*)&addrServer, sizeof(addrServer)) == SOCKET_ERROR)
			{
				closesocket(*socListen);
				WSACleanup();
				throw "error bind failed";
			}

			if (listen(*socListen, SOMAXCONN) == SOCKET_ERROR)
			{
				closesocket(*socListen);
				WSACleanup();
				throw "error : listen failed";
			}

			SOCKADDR_IN addrClient;
			int addrSize = sizeof(addrClient);
			*socClient = accept(*socListen, (SOCKADDR*)&addrClient, &addrSize);

			if (*socClient == INVALID_SOCKET)
			{
				closesocket(*socListen);
				closesocket(*socClient);
				WSACleanup();
				throw "error : accept failed";
			}

			closesocket(*socListen);
		}

		void tcp::openClient(const std::string& serverIp_, const int port_)
		{
			WSADATA wsaData;
			if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
			{
				//return "error : WSAStartup failed";
			}

			SOCKET socClient = INVALID_SOCKET;
			if (socket(PF_INET, SOCK_STREAM, IPPROTO_TCP) == INVALID_SOCKET)
			{
				WSACleanup();
				//return "error : clientSocket stop";
			}

			SOCKADDR_IN tAddr;
			tAddr.sin_family = AF_INET;
			tAddr.sin_port = htons(port_);
			inet_pton(AF_INET, serverIp_.c_str(), &(tAddr.sin_addr.s_addr));
		}

		std::string tcp::receive()
		{
			char buffer[512];

			if (recv(*socClient, buffer, 512, 0) == SOCKET_ERROR)
			{
				closesocket(*socClient);	// 고려해보기.
				throw "error : accept failed";
			}

			return buffer;
		}

		bool tcp::sendM()
		{
			char buffer[512] = "exampleTestVersion";

			if (send(*socClient, buffer, 512, 0) == SOCKET_ERROR)
			{
				return "error : server error send";
			}
		}
	}
}




