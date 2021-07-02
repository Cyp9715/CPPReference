#include "cypCppReference.h"

namespace cyp
{
	namespace string
	{
		bool isContain(const std::string& input, const std::string& find)
		{
			if (input.find(find) == std::string::npos)
			{
				return false;
			}
			else
			{
				return true;
			}
		}

		void changeStr(std::string& str, const std::string& find, const std::string& change)
		{
			size_t ui_num = str.find(find);

			while (true)
			{
				if (ui_num == std::string::npos)
				{
					return;
				}
				else
				{
					str.erase(ui_num, find.size());
					str.insert(ui_num, change);
				}
				ui_num = str.find(find, change.size());
			}
		}

		bool isAlphabet(const std::string& str)
		{
			for (size_t i = 0; i < str.size(); ++i)
			{
				if ((str[i] >= 97 && 122 >= str[i]) || (str[i] >= 65 && 90 >= str[i]))
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

		bool isNumber(const std::string& str)
		{
			return !str.empty() && std::find_if(str.begin(), str.end(),
				[](unsigned char c) { return !std::isdigit(c); }) == str.end();
		}

		void toLower(std::string& str)
		{
			std::transform(str.begin(), str.end(), str.begin(),	[](unsigned char c) { return std::tolower(c); });
		}

		void toUpper(std::string& str)
		{
			std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::toupper(c); });
		}

		void removeContinuousChar(std::string& str, char target)
		{
			for (int i = 0; i < str.length() - 1; ++i)
			{
				if (str[i] == target && str[i+1] == target)
				{
					str.erase(i, 1);
					--i;
				}
			}
		}

		std::string removeExtension(const std::string& fileName, bool removeMultiExtension)
		{
			std::string temp_ = fileName;
			auto point = temp_.find('.');

			if (point == std::string::npos)
			{
				return "cyp::string::removeExtension() no exist extension point '.'";
			}

			if (removeMultiExtension)
			{
				temp_.erase(point);
			}
			else
			{
				auto rpoint = temp_.rfind('.');
				temp_.erase(rpoint);
			}

			return temp_;
		}

	}

	namespace vector
	{
		template<typename T>
		bool isContain(const std::vector<T>& v_input, const T find)
		{
			if (std::find(v_input.begin(), v_input.end(), find) != v_input.end())
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
		bool deleteFile(const std::string& filePath)
		{
			return std::filesystem::remove(filePath) ? true : false;
		}

		bool createDirectory(const std::string& directoryLoc)
		{
			return std::filesystem::create_directory(directoryLoc) ? true : false;
		}

		void createFile(const std::string& filePath, const std::string& fileContent)
		{
			std::ofstream file(filePath);
			file << fileContent;
			file.close();
		}

		std::string readAllFile(const std::string& fileLoc)
		{
			std::ifstream file(fileLoc);
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

			if(bind(recvSocket, (SOCKADDR*)&sendAddr, sizeof(sendAddr)) == BIND_ERROR)
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

	namespace hash
	{
		std::string MD::strToMD5(const std::string& str)
		{
			byte digest[CryptoPP::Weak::MD5::DIGESTSIZE];

			CryptoPP::Weak::MD5 hash;
			hash.CalculateDigest(digest, (const byte*)str.c_str(), str.length());

			CryptoPP::HexEncoder encoder;
			std::string output;

			encoder.Attach(new CryptoPP::StringSink(output));
			encoder.Put(digest, sizeof(digest));
			encoder.MessageEnd();

			return output;
		}

		std::string MD::fileToMD5(const std::string filePath)
		{
			CryptoPP::Weak::MD5 md;
			const size_t size = CryptoPP::Weak::MD5::DIGESTSIZE * 2;
			byte buf[size] = { 0 };
			CryptoPP::FileSource filesource(
				filePath.c_str(), true,
				new CryptoPP::HashFilter(
					md, new CryptoPP::HexEncoder(new CryptoPP::ArraySink(buf, size))));
			std::string output = std::string(reinterpret_cast<const char*>(buf), size);

			return output;
		}
		
		std::string SHA::strToSHA1(const std::string& str)
		{
			CryptoPP::SHA1 hash;
			std::string output;

			CryptoPP::StringSource s(str, true, new CryptoPP::HashFilter(hash,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(output))));

			return output;
		}

		std::string SHA::fileToSHA1(const std::string& filePath)
		{
			CryptoPP::SHA1 hash;
			std::string output;

			CryptoPP::FileSource f(filePath.c_str(), true,
				new CryptoPP::HashFilter(hash,
					new CryptoPP::HexEncoder(new
						CryptoPP::StringSink(output))));

			return output;
		}

		std::string SHA::strToSHA2_256(const std::string& str)
		{
			CryptoPP::SHA256 hash;
			std::string output;

			CryptoPP::StringSource s(str, true, new CryptoPP::HashFilter(hash, 
												new CryptoPP::HexEncoder(new CryptoPP::StringSink(output))));

			return output;
		}

		std::string SHA::fileToSHA2_256(const std::string& filePath)
		{
			CryptoPP::SHA256 hash;
			std::string output;

			CryptoPP::FileSource f(filePath.c_str(), true,
				new CryptoPP::HashFilter(hash,
					new CryptoPP::HexEncoder(new
						CryptoPP::StringSink(output))));

			return output;
		}

		std::string SHA::strToSHA2_512(const std::string& str)
		{
			CryptoPP::SHA512 hash;
			std::string output;

			CryptoPP::StringSource s(str, true, new CryptoPP::HashFilter(hash,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(output))));

			return output;
		}

		std::string SHA::fileToSHA2_512(const std::string& filePath)
		{
			CryptoPP::SHA512 hash;
			std::string output;

			CryptoPP::FileSource f(filePath.c_str(), true,
				new CryptoPP::HashFilter(hash,
					new CryptoPP::HexEncoder(new
						CryptoPP::StringSink(output))));

			return output;
		}

		std::string SHA::strToSHA3_256(const std::string& str)
		{
			CryptoPP::SHA3_256 hash;
			std::string output;

			CryptoPP::StringSource s(str, true, new CryptoPP::HashFilter(hash,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(output))));

			return output;
		}

		std::string SHA::fileToSHA3_256(const std::string& filePath)
		{
			CryptoPP::SHA3_256 hash;
			std::string output;

			CryptoPP::FileSource f(filePath.c_str(), true,
				new CryptoPP::HashFilter(hash,
					new CryptoPP::HexEncoder(new
						CryptoPP::StringSink(output))));

			return output;
		}

		std::string SHA::strToSHA3_512(const std::string& str)
		{
			CryptoPP::SHA3_512 hash;
			std::string output;

			CryptoPP::StringSource s(str, true, new CryptoPP::HashFilter(hash,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(output))));

			return output;
		}

		std::string SHA::fileToSHA3_512(const std::string& filePath)
		{
			CryptoPP::SHA3_512 hash;
			std::string output;

			CryptoPP::FileSource f(filePath.c_str(), true, 
								new CryptoPP::HashFilter(hash,
									new CryptoPP::HexEncoder(new 
										CryptoPP::StringSink(output))));

			return output;
		}
	}


	namespace command
	{
		void systemCmd(const std::string& command)
		{
			system(command.c_str());
		}

		void popenCmd(const std::string& command)
		{
			FILE* pipe = _popen(command.c_str(), "r");
			if (!pipe) throw std::runtime_error("popen() failed");
		}

		std::string getStrPopenCmd(const std::string& command)
		{
			char buffer[128];
			std::string result = "";
			FILE* pipe = _popen(command.c_str(), "r");
			if (!pipe) throw std::runtime_error("popen() failed!");
			try
			{
				while (fgets(buffer, sizeof buffer, pipe) != NULL)
				{
					result += buffer;
				}
			}
			catch (...)
			{
				_pclose(pipe);
				throw;
			}
			_pclose(pipe);
			return result;
		}
	}
}

