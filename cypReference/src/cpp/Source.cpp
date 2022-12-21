#include "cyp_file.hpp"
#include "cyp_timer.hpp"
#include <thread>

double aa;


void test(std::string msg)
{
	cyp::timer::Timer time;
	time.Start();

	cyp::file::FileCommunication::FileReceive fs;
	int port = 43000;
	std::string ip = "127.0.0.1";
	std::string filePath = "C:\\Users\\Cyphe\\바탕 화면\\한동교.zip";
	fs.ReceiveFile(ip, port, filePath, aa);

	//cyp::file::FileCommunication::FileSend fs_s;
	//int port = 43000;
	//std::string ip = "127.0.0.1";
	//std::string filepath = "c:\\video.zip";
	//fs_s.SendFile(43000, filepath);

	std::cout << time.getTime<std::chrono::seconds>();
}

int main()
{
	std::thread th(test, "ss");

	while (true)
	{
		std::cout << aa << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}