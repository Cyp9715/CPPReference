#include "cyp_communication.hpp"

int main()
{
	cyp::communication::Udp_multicast udp;
	udp.open_send("224.100.100.99", 3001);
	udp.send("444");

	udp.open_receive("224.100.100.99", 3001);
	std::cout <<  udp.receive() << std::endl;
	int a;
	std::cin >> a;
}