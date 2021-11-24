#include "cyp_file.hpp"

int main()
{
	cyp::file::FileCommunication f;

	f.sendFile("192.168.100.32", 9998, "C:\\Users\\Cyp\\Desktop\\test.txt");
	Sleep(2000);
}
