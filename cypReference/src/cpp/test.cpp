#include "cyp_file.hpp"

void aaa(std::string&& a)
{
	std::cout << "aa" << std::endl;
}

int main()
{
	cyp::file::FileCommunication::FileSend f;
	f.sendFile("192.168.100.32", 9998, "C:\\Users\\Cyp\\Desktop\\mdfkkkkk.mdf");
	
	std::string aa = "123";
	aaa("123");

}
