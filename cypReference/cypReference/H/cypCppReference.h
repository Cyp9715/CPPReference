#pragma once

// string
#include <string>

// vector
#include <vector>

// file
#include <filesystem>
#include <ostream>
#include <fstream>

// communication
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32")

namespace cyp
{
	namespace string
	{
		static bool isAlphabet(const std::string& str_);
		static bool isContain(const std::string& original, const std::string& find_);
		static void changeStr(std::string& str_, const std::string& find_, const std::string& change);
		static bool isNumber(const std::string& str_);
	};

	namespace vector
	{
		template<typename T>
		static bool isContain(const std::vector<T>& v_input, const T find_);
	};

	namespace file
	{
		static bool deleteFile(const std::string& fileLoc_);
		static bool createDirectory(const std::string& directoryLoc_);
		static void createFile(const std::string& fileName_, const std::string& fileContent_ = "");
		static std::string readAllFile(const std::string& fileName_);
	}

	namespace communication
	{
		class tcp
		{
		private:
			WSADATA wsaData;

			std::unique_ptr<SOCKET> socListen = std::make_unique<SOCKET>();
			std::unique_ptr<SOCKET> socClient = std::make_unique<SOCKET>();

		public:
			tcp();
			~tcp();

			void openServer(const int port_);
			void openClient(const std::string& serverIp_, const int port_);

			std::string receive();
			bool sendM();

		};

		class udp
		{
			udp();
			~udp();

			bool sendM();
			bool receiveM();
		};
	}
};