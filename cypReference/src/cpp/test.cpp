#include "cyp_communication.hpp"

int main()
{
	cyp::communication::Tcp tcp;
	tcp.openClient("192.168.200.134", 9999);
	std::cout << tcp.receiveClient();
}