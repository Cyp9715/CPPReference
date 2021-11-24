#include "cyp_file.hpp"

int main()
{
	cyp::file::FileCommunication f;

	f.sendFile("192.168.100.32", 9998, "C:\\Users\\Cyp\\Desktop\\test.txt");
	Sleep(2000);

	////open file
	////std::ifstream infile("C:\\Users\\Cyp\\Desktop\\test.txt");
	////std::vector<char> buffer;

	////get length of file
	////infile.seekg(0, infile.end);
	////size_t length = infile.tellg();
	////infile.seekg(0, infile.beg);

	////read file
	////if (length > 0) {
	////	buffer.resize(length);
	////	infile.read(&buffer[0], length);
	////}
}
