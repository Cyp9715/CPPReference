#include "cypCppReference.h"


bool cyp::string::isContain(const std::string& input_, const std::string find_)
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

void cyp::string::changeStr(std::string& input_, const std::string& find_, const std::string& change)
{
	size_t ui_num = input_.find(find_);

	while (true)
	{
		if (ui_num == std::string::npos)
		{
			return;
		}
		else
		{
			input_.erase(ui_num, find_.size());
			input_.insert(ui_num, change);
		}
		ui_num = input_.find(find_, change.size());
	}
}

bool cyp::string::isAlphabet(const std::string& input_)
{
	for (size_t i = 0; i < input_.size(); ++i)
	{
		if ((input_[i] >= 97 && 122 >= input_[i]) || (input_[i] >= 65 && 90 >= input_[i]))
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

bool cyp::string::isNumber(const std::string& input_)
{
	return !input_.empty() && std::find_if(input_.begin(), input_.end(), 
		[](unsigned char c) { return !std::isdigit(c); }) == input_.end();
}

template<typename T>
bool cyp::vector::isContain(const std::vector<T>& v_input, const T find_)
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

bool cyp::file::deleteFile(const std::string& fileLoc_)
{
	return std::filesystem::remove(fileLoc_) ? true : false;
}

bool cyp::file::createDirectory(const std::string& directoryLoc_)
{
	return std::filesystem::create_directory(directoryLoc_) ? true : false;
}

void cyp::file::createFile(const std::string& fileName_, const std::string& fileContent_)
{
	std::ofstream file(fileName_);
	file << fileContent_;
	file.close();
}

std::string cyp::file::readAllFile(const std::string& fileName_)
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

void cyp::communication::tcp::openServer(const int port_)
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

void cyp::communication::tcp::openClient(const std::string& serverIp_, const int port_)
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
	inet_pton(AF_INET, serverIp_.c_str() , &(tAddr.sin_addr.s_addr));
}

std::string cyp::communication::tcp::receive()
{
	char buffer[512];

	if (recv(*socClient, buffer, 512, 0) == SOCKET_ERROR)
	{
		closesocket(*socClient);	// 고려해보기.
		throw "error : accept failed";
	}

	return buffer;
}

bool cyp::communication::tcp::sendM()
{
	char buffer[512] = "exampleTestVersion";

	if (send(*socClient, buffer, 512, 0) == SOCKET_ERROR)
	{
		return "error : server error send";
	}
}
